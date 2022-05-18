#pragma once
#include "AirlineBook.h"

AirlineBook::AirlineBook() {
	this->dates = { "5/11", "5/12", "5/13", "5/14", "5/15", "5/16", "5/17" };
	this->airports = { "인천", "김포", "김해", "청주", "제주" };

	// 비행편 데이터 준비
	for (auto& date : this->dates) {
		for (auto& airport1 : this->airports) {
			for (auto& airport2 : this->airports) {
				if (airport1 == airport2) {
					continue;
				}

				this->flights.push_back(new AirlineBookFlight(airport1, airport2, date, 9, 10));
				this->flights.push_back(new AirlineBookFlight(airport1, airport2, date, 14, 15));
				this->flights.push_back(new AirlineBookFlight(airport1, airport2, date, 19, 20));
			}
		}
	}
}

AirlineBook::~AirlineBook() {
	for (auto& flight : flights) {
		delete flight;
	}
	this->flights.clear();

	for (auto& ticket : tickets) {
		delete ticket;
	}
	this->tickets.clear();
}

void AirlineBook::run() {
	AirlineBookConsole::printWelcomeMsg();

	//// 로그인 후 유저 받아오기
	UserManager* pManager = &this->manager;
	AirlineBookLogin login(pManager);
	login.login();
	AirlineBookUser& thisUser = (AirlineBookUser&)login.getUser();

	while (true) {
		int selectedMenu = AirlineBookConsole::selectMenu();

		if (selectedMenu == 1) {
			reserve(thisUser.getID());
		}
		else if (selectedMenu == 2) {
			cancel(thisUser.getID());
		}
		else if (selectedMenu == 3) {
			show(thisUser.getID());
		}
		else if (selectedMenu == 4) {
			stat(thisUser.getID());
		}
		else if (selectedMenu == 5) {
			AirlineBookConsole::printExitMsg();
			break;
		}
	}
}

void AirlineBook::reserve(string id) {
	AirlineBookUser& thisUser = (AirlineBookUser&)this->manager.getUser(id);

	AirlineBookConsole::printUserData(thisUser);

	string date = AirlineBookConsole::selectDate(this->dates);

	SelectAirport:
	string departureAirport = AirlineBookConsole::selectDepartureAirport();
	string arrivalAirport = AirlineBookConsole::selectArrivalAirport();
	
	if (departureAirport == arrivalAirport) {
		AirlineBookConsole::printSameAirportMsg();
		goto SelectAirport;
	}

	bool isRound = AirlineBookConsole::selectRoundTicket();

	vector<AirlineBookFlight*> searchedFlights;
	for (auto& pFlight : this->flights) {
		AirlineBookFlight& flight = *pFlight;

		if (flight.getDate() != date) {
			continue;
		}
		if (flight.getDepartureAirport() != departureAirport) {
			continue;
		}
		if (flight.getArrivalAirport() != arrivalAirport) {
			continue;
		}

		searchedFlights.push_back(pFlight);
	}

	int selectedFlight = AirlineBookConsole::selectFlight(searchedFlights);
	AirlineBookFlight& thisFlight = *searchedFlights[selectedFlight - 1];

	SelectSeat:
	int selectedSeat = AirlineBookConsole::selectSeat(thisFlight, thisUser.getMoney());
	if (thisUser.getMoney() < thisFlight.getSeat(selectedSeat).getPrice()) {
		AirlineBookConsole::printNotEnoughMoney();
		goto SelectSeat;
	}

	thisFlight.getSeat(selectedSeat).reserve(id);
	tickets.push_back(new AirlineBookTicket(id, &thisFlight, selectedSeat));
	thisUser.subtractMoney(thisFlight.getSeat(selectedSeat).getPrice());
	thisUser.addMileage(100);
	thisUser.increaseBookCount();

	AirlineBookConsole::printReserveCompleteMsg();
	AirlineBookConsole::printENDL();

	if (isRound) {
		AirlineBookConsole::printRoundTicketMsg();

		vector<string> newdate;
		vector<AirlineBookFlight*> roundsearchedFlights;

		string ndates[7] = { "5/11", "5/12", "5/13", "5/14", "5/15", "5/16", "5/17" };
		int temp;
		for (int i = 0; i < 7; i++) {
			if (ndates[i] == date) {
				temp = i;
				break;
			}
		}
		for (int i = temp; i < 7; i++) {
			newdate.push_back(ndates[i]);
		}

		for (auto& flight : this->flights) {
			//이후인가?
			bool isExist = false;
			for (auto& newnewdate : newdate) {
				if (newnewdate == flight->getDate()) {
					isExist = true;
				}
			}
			if (!isExist) {
				continue;
			}

			if (flight->getDepartureAirport() != arrivalAirport) {
				continue;
			}
			if (flight->getArrivalAirport() != departureAirport) {
				continue;
			}
			if (flight->getDate() == thisFlight.getDate() && (flight->getDepartureTime() < thisFlight.getArrivalTime())) {
				continue;
			}
			roundsearchedFlights.push_back(flight);
		}


		int roundselectedFlight = AirlineBookConsole::selectFlight(roundsearchedFlights);
		AirlineBookFlight& roundthisFlight = *roundsearchedFlights[roundselectedFlight - 1];

		roundSelectSeat:
		int roundselectedSeat = AirlineBookConsole::selectSeat(roundthisFlight, thisUser.getMoney());
		if (thisUser.getMoney() < roundthisFlight.getSeat(selectedSeat).getPrice()) {
			AirlineBookConsole::printNotEnoughMoney();
			goto roundSelectSeat;
		}

		roundthisFlight.getSeat(roundselectedSeat).reserve(id);
		tickets.push_back(new AirlineBookTicket(id, &roundthisFlight, roundselectedSeat));
		thisUser.subtractMoney(roundthisFlight.getSeat(roundselectedSeat).getPrice());
		thisUser.addMileage(100);
		thisUser.increaseBookCount();

		AirlineBookConsole::printReserveCompleteMsg();
		AirlineBookConsole::printENDL();


	}

}

void AirlineBook::show(string id) {
	vector<AirlineBookTicket*> searchedTickets;
	for (auto& pTicket : this->tickets) {
		if (pTicket->getCustomerID() == id) {
			searchedTickets.push_back(pTicket);
		}
	}
	if (searchedTickets.empty()) {
		AirlineBookConsole::printNotExistTicket();
		return;
	}
	int selectedTicket = AirlineBookConsole::selectShowTicket(searchedTickets);
	if (selectedTicket != 0) {
		//업데이트필요.
		AirlineBookConsole::printSeats(searchedTickets[selectedTicket - 1]->getFlight(), id);
	}
}

void AirlineBook::cancel(string id) {
	vector<AirlineBookTicket*> searchedTickets;
	for (auto& pTicket : this->tickets) {
		if (pTicket->getCustomerID() == id) {
			searchedTickets.push_back(pTicket);
		}
	}
	if (searchedTickets.empty()) {
		AirlineBookConsole::printNotExistTicket();
		return;
	}

	int selectedTicket = AirlineBookConsole::selectCancelTicket(searchedTickets);

	AirlineBookTicket* pThisTicket = searchedTickets[selectedTicket - 1];
	pThisTicket->getFlight().getSeat(pThisTicket->getSeatNum()).cancel();
	AirlineBookUser& thisUser = (AirlineBookUser&)manager.getUser(id);

	thisUser.addMoney(pThisTicket->getFlight().getSeat(pThisTicket->getSeatNum()).getPrice());
	thisUser.subtractMileage(100);
	thisUser.decreaseBookCount();

	for (int i = 0; i < tickets.size(); i++) {
		if (tickets[i] == pThisTicket) {
			tickets.erase(tickets.begin() + i);
			i--;
		}
	}
}

void AirlineBook::stat(string id) {
	AirlineBookConsole::printStatBookCount((AirlineBookUser&)manager.getUser(id));
	AirlineBookConsole::printStatSeatCount(this->tickets);
}
