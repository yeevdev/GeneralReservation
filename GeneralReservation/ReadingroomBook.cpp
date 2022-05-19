#include "ReadingroomBook.h"
#include "ReadingroomBookSeat.h"
#include "ReadingroomBookUser.h"
#include "ReadingroomBookConsole.h"
#include "ReadingroomBookLogin.h"

ReadingroomBook::ReadingroomBook() {
	for (int i = 0; i < 15; i++) {
		vector<ReadingroomBookSeat*> tempVector;
		for (int j = 0; j < 15; j++) {
			tempVector.push_back(new ReadingroomBookSeat());
		}

		this->seats.push_back(tempVector);
	}

	for (int i = 1; i <= 300; i++) {
		this->manager.addUser(new ReadingroomBookUser(to_string(i), "", "세대" + to_string(i)));
	}
}

void ReadingroomBook::run() {
	ReadingroomBookConsole::printWelcomeMsg();

	ReadingroomBookLogin login(&this->manager);
	login.login();
	ReadingroomBookUser& thisUser = (ReadingroomBookUser&)login.getUser();

	while (true) {
		int selectedMenu = ReadingroomBookConsole::selectMenu();

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
			stat();
		}
		else if (selectedMenu == 5) {
			Console::clear();
			ReadingroomBookConsole::printExitMsg();
			break;
		}
	}
	
}

bool temp1(UserManager& manager, vector<vector<ReadingroomBookSeat*>>& seats, int i, int j, int start, int end, string gender) {
	bool seeGender = true;
	for (int k = start - 9; k <= end - 10; k++) {
		ReadingroomBookSeat* aroundSeats[4];
		ReadingroomBookSeat* upSeat = nullptr;
		ReadingroomBookSeat* downSeat = nullptr;
		ReadingroomBookSeat* leftSeat = nullptr;
		ReadingroomBookSeat* rightSeat = nullptr;

		if (i > 0 && i < 14 && j > 0 && j < 14) {
			upSeat = seats[i - 1][j];
			downSeat = seats[i + 1][j];
			leftSeat = seats[i][j - 1];
			rightSeat = seats[i][j + 1];
		}
		if (i == 0) {
			upSeat = nullptr;
			downSeat = seats[i + 1][j];

			if (j == 0) {
				leftSeat = nullptr;
			}
			else if (j == 14) {
				rightSeat = nullptr;
			}
			else {
				leftSeat = seats[i][j - 1];
				rightSeat = seats[i][j + 1];
			}
		}
		if (i == 14) {
			upSeat = seats[i - 1][j];
			downSeat = nullptr;

			if (j == 0) {
				leftSeat = nullptr;
			}
			else if (j == 14) {
				rightSeat = nullptr;
			}
			else {
				leftSeat = seats[i][j - 1];
				rightSeat = seats[i][j + 1];
			}
		}

		aroundSeats[0] = upSeat;
		aroundSeats[1] = downSeat;
		aroundSeats[2] = leftSeat;
		aroundSeats[3] = rightSeat;

		string genders[4];
		for (int i = 0; i < 4; i++) {
			string newid = aroundSeats[i]->getCustomerID(k + 1);
			if (!manager.isUserExist(newid)) {
				genders[i] = "";
				continue;
			}
			ReadingroomBookUser& thatUser = (ReadingroomBookUser&)manager.getUser(newid);
			genders[i] = thatUser.getGender();
		}

		for (auto& thisGender : genders) {
			if (thisGender == gender) {
				seeGender = false;
			}
		}
	}
	return seeGender;
}

void ReadingroomBook::reserve(string id) {
	ReadingroomBookConsole::printReserveMsg();

	int timeStart = ReadingroomBookConsole::getStartTime();
	int timeEnd = ReadingroomBookConsole::getEndTime();

	ReadingroomBookConsole::printSeats(this->manager, seats, id, timeStart, timeEnd);

	int row = ReadingroomBookConsole::getRow();
	int culumn = ReadingroomBookConsole::getCulumn();

	bool canReserve = true;
	ReadingroomBookUser& mymyUser = (ReadingroomBookUser&)manager.getUser(id);
	string gender = mymyUser.getGender();
	ReadingroomBookSeat* thisSeat = seats[row-1][culumn-1];
	for (int k = timeStart - 9; k <= timeEnd - 10; k++) {
		if (thisSeat->isReserved(k+1) == true) {
			canReserve = false;
		}
	}

	if (!temp1(manager, seats, row - 1, culumn - 1, timeStart, timeEnd, gender)) {
		canReserve = false;
	}

	if (canReserve) {
		thisSeat->reserve(id, timeStart, timeEnd);
		if (gender == "남자") {
			maleCount++;
		}
		else {
			femaleCount++;
		}
		this->reservations.push_back(new ReadingroomBookReservation(id, thisSeat, timeStart, timeEnd));
		Console::clear();
		ReadingroomBookConsole::printReserveCompleteMsg();
	}
	else {
		Console::clear();
		ReadingroomBookConsole::printReserveFailMsg();
	}
}

void ReadingroomBook::cancel(string id) {
	if (reservations.empty()) {
		ReadingroomBookConsole::printNotExistReservationMsg();
		return;
	}

	ReadingroomBookReservation* pMyReservation = nullptr;
	for (auto& reservation : reservations) {
		if (reservation->getID() == id) {
			pMyReservation = reservation;
		}
	}

	if (pMyReservation == nullptr) {
		ReadingroomBookConsole::printNotExistReservationMsg();
		return;
	}

	pMyReservation->getSeat().cancel(id);
	ReadingroomBookUser& mymyUser = (ReadingroomBookUser&)manager.getUser(id);
	string gender = mymyUser.getGender();
	if (gender == "남자") {
		maleCount--;
	}
	else {
		femaleCount--;
	}
	ReadingroomBookConsole::printCancelCompleteMsg();



}

void ReadingroomBook::show(string id) {
	ReadingroomBookConsole::showSeats(reservations, id);
}

void ReadingroomBook::stat() {
	ReadingroomBookConsole::showStat(maleCount, femaleCount);
}
