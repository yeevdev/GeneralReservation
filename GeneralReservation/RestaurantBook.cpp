#include "RestaurantBook.h"
#include "RestaurantBookConsole.h"
#include "RestaurantBookLogin.h"
#include "RestaurantBookUser.h"

RestaurantBook::RestaurantBook() {
	tables.push_back(new RestaurantBookTable(1, 2));
	tables.push_back(new RestaurantBookTable(2, 2));
	tables.push_back(new RestaurantBookTable(3, 4));
	tables.push_back(new RestaurantBookTable(4, 4));
	tables.push_back(new RestaurantBookTable(5, 6));
	tables.push_back(new RestaurantBookTable(6, 6));
}

RestaurantBook::~RestaurantBook() {
	for (auto& table : this->tables) {
		delete table;
	}
	this->tables.clear();

	for (auto& reservation : this->reservations) {
		delete reservation;
	}
	this->reservations.clear();

	this->waitings.clear();
}

void RestaurantBook::run() {
	RestaurantBookConsole::printWelcomeMsg();

	UserManager* pManager = &this->manager;
	RestaurantBookLogin login(pManager);
	login.login();
	RestaurantBookUser& thisUser = (RestaurantBookUser&)login.getUser();

	while (true) {
		int selectedMenu = RestaurantBookConsole::selectMenu();

		if (selectedMenu == 1) {
			reserve(thisUser.getID());
		}
		else if (selectedMenu == 2) {
			cancel(thisUser.getID());
		}
		else if (selectedMenu == 3) {
			wait(thisUser.getID());
		}
		else if (selectedMenu == 4) {
			show(thisUser.getID());
		}
		else if (selectedMenu == 5) {
			completeEating(thisUser.getID());
		}
		else if (selectedMenu == 6) {
			stat();
		}
		else if (selectedMenu == 7) {
			RestaurantBookConsole::printExitMsg();
			break;
		}
	}
}

void RestaurantBook::reserve(string id) {
	RestaurantBookUser& thisUser = (RestaurantBookUser&)manager.getUser(id);

	int peopleNum = RestaurantBookConsole::getPeopleNum();
	int selectedTable = RestaurantBookConsole::selectTable(tables, peopleNum);

	RestaurantBookTable& thisTable = *tables[selectedTable - 1];

	thisTable.reserve(id);
	reservations.push_back(new RestaurantBookReservation(id, &thisTable, peopleNum));

	RestaurantBookConsole::printReserveCompleteMsg();
}

void RestaurantBook::cancel(string id) {
	if (reservations.empty() && waitings.empty()) {
		RestaurantBookConsole::printNotExistReservationMsg();
		return;
	}

	RestaurantBookReservation* pMyReservation = nullptr;
	for (auto& reservation : reservations) {
		if (reservation->getCustomerID() == id) {
			pMyReservation = reservation;
		}
	}
	
	pMyReservation->getTable().cancel();
	RestaurantBookConsole::printCancelCompleteMsg();

	for (int i = 0; i < reservations.size(); i++) {
		if (reservations[i] == pMyReservation) {
			delete pMyReservation;
			reservations.erase(reservations.begin() + i);
			i--;
		}
	}
}

void RestaurantBook::wait(string id) {
	RestaurantBookUser& thisUser = (RestaurantBookUser&)manager.getUser(id);

	int peopleNum = RestaurantBookConsole::getPeopleNum();

	bool canEnter = !(tables[1]->isEating() && tables[3]->isEating() && tables[5]->isEating());
	if (this->waitings.empty() && canEnter) {
		thisUser.setEating(true);
		if (!tables[1]->isEating()) {
			tables[1]->eat();
		}
		else if (!tables[3]->isEating()) {
			tables[3]->eat();
		}
		else if (!tables[5]->isEating()) {
			tables[5]->eat();
		}
	}
	else {
		waitings.push_back(id);
	}
	
}

void RestaurantBook::show(string id) {
	RestaurantBookUser& thisUser = (RestaurantBookUser&)manager.getUser(id);

	if (thisUser.isEating()) {
		RestaurantBookConsole::printIsEatingMsg();
		return;
	}

	RestaurantBookReservation* pMyReservation = nullptr;
	for (auto& reservation : reservations) {
		if (reservation->getCustomerID() == id) {
			pMyReservation = reservation;
		}
	}

	if (!(pMyReservation == nullptr)) {
		RestaurantBookConsole::printShowReservation(*pMyReservation);
	}

	bool isWaiting = false;
	int count;
	int i = 0;
	for (auto& waitID : waitings) {
		if (waitID == id) {
			isWaiting = true;
			count = i;
		}
		i++;
	}

	if (waitings.empty()) {
		RestaurantBookConsole::printNotExistWaitingMsg();
	}
	else if(isWaiting) {
		RestaurantBookConsole::printNowWaitingMsg(waitings, count);
	}
	else {
		RestaurantBookConsole::printWaitingMsg(waitings);
	}
}

void RestaurantBook::completeEating(string id) {
	RestaurantBookUser& thisUser = (RestaurantBookUser&)manager.getUser(id);
	
	if (!thisUser.isEating()) {
		RestaurantBookConsole::printNotEating();
		return;
	}

	if (tables[1]->isEating()) {
		tables[1]->complete();
	}
	else if (tables[3]->isEating()) {
		tables[3]->complete();
	}
	else if (tables[5]->isEating()) {
		tables[5]->complete();
	}

	thisUser.setEating(false);

	if (!waitings.empty()) {
		RestaurantBookUser& thatUser = (RestaurantBookUser&)manager.getUser(waitings[0]);
		waitings.erase(waitings.begin());

		thatUser.setEating(true);
		if (!tables[1]->isEating()) {
			tables[1]->eat();
		}
		else if (!tables[3]->isEating()) {
			tables[3]->eat();
		}
		else if (!tables[5]->isEating()) {
			tables[5]->eat();
		}
	}
}

void RestaurantBook::stat() {
	RestaurantBookConsole::printStat();
	for (auto& table : tables) {
		RestaurantBookConsole::printStatTable(table->getTableNum(), table->getReservedCount());
	}
}
