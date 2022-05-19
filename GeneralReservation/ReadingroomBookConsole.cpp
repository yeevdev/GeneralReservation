#include "ReadingroomBookConsole.h"
#include "ReadingroomBookUser.h"
#include "ReadingroomBookReservation.h"

int ReadingroomBookConsole::getAge() {
	cout << "나이를 입력하세요. >> ";
	return getInt();
}

int ReadingroomBookConsole::getStartTime() {
	cout << "시작시간을 입력하세요.(9,13, 17, 23 등의 형식으로 입력하세요.) >> ";

	return getInt();
}

int ReadingroomBookConsole::getEndTime() {
	cout << "종료시간을 입력하세요.(9,13, 17, 23 등의 형식으로 입력하세요.) >> ";

	return getInt();
}

int ReadingroomBookConsole::getRow() {
	cout << "예약할 좌석의 행을 입력하세요. >> ";
	return getInt();
}

int ReadingroomBookConsole::getCulumn() {
	cout << "예약할 좌석의 열을 입력하세요. >> ";
	return getInt();
}

string ReadingroomBookConsole::getGender() {
	cout << "성별(남자 / 여자) >> ";
	return getString();
}

void ReadingroomBookConsole::printLoginStartMsg() {
	cout << "로그인이 필요합니다.  ID는 세대번호입니다." << endl;
}

void ReadingroomBookConsole::printWelcomeMsg() {
	cout << "***** 홍익독서실에 오신 것을 환영합니다." << endl;
}

void ReadingroomBookConsole::printExitMsg() {
	cout << "***** 식당 예약 프로그램에서 로그아웃 합니다. *****" << endl;
}

void ReadingroomBookConsole::printReserveMsg() {
	cout << "[ □: 예약 가능한 좌석, ■: 이미 예약된 좌석 ]" << endl;
	cout << "[ " << ANSI_COLOR_CYAN << "■" << ANSI_COLOR_RESET << ": 남자 예약석, " << ANSI_COLOR_MAGENTA << "■" << ANSI_COLOR_RESET << ": 여자 예약석 ]" << endl;
	cout << "[ 앞, 뒤, 양옆에 동성끼리 앉을 수 없습니다. ]" << endl;
	cout << "[ 독서실 이용시간은 09:00 ~ 23:00 입니다. 1시간 단위로 예약가능합니다. ]" << endl;
	cout << "[ 예) 9시 시작, 13시 종료  ->  09:00 ~ 13:00 이용 예약 ]" << endl;
}

bool temp(UserManager& manager, vector<vector<ReadingroomBookSeat*>>& seats, int i, int j, int start, int end, string gender) {
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

void ReadingroomBookConsole::printSeats(UserManager& manager, vector<vector<ReadingroomBookSeat*>>& seats, string id, int start, int end) {
	printENDL();
	cout << "     [01열] [02열] [03열] [04열] [05열] [06열] [07열] [08열] [09열] [10열] [11열] [12열] [13열] [14열] [15열]" << endl;
	ReadingroomBookUser& myUser = (ReadingroomBookUser&)manager.getUser(id);
	for (int i = 0; i < 15; i++) {
		cout << "[" << Console::getFormattedInt(i + 1) << "행] ";
		for (int j = 0; j < 15; j++) {
			ReadingroomBookSeat* thisSeat = seats[i][j];
			
			bool canReserve = true;
			string gender;
			for (int k = start - 9; k <= end - 10; k++) {
				if (thisSeat->isReserved(k+1) == true) {
					//cout << "이거임 >" << thisSeat->isReserved(k + 1) << "?" << k << "< 이거임";
					string newnewid = thisSeat->getCustomerID(k + 1);

					ReadingroomBookUser& thisUser = (ReadingroomBookUser&)manager.getUser(newnewid);
					gender = thisUser.getGender();
					canReserve = false;
				}
			}
			if (!canReserve) {
				if (gender == "남자") {
					cout << ANSI_COLOR_CYAN;
				}
				else {
					cout << ANSI_COLOR_MAGENTA;
				}
				cout << " ■    " << ANSI_COLOR_RESET;
			}
			else {
				cout << " □    " << ANSI_COLOR_RESET;
			}
		}
		cout << endl;
	}
}

void ReadingroomBookConsole::printReserveCompleteMsg() {
	cout << "해당 좌석을 예약했습니다." << endl;
}

void ReadingroomBookConsole::printReserveFailMsg() {
	cout << "해당 좌석을 예약하는데 실패했습니다." << endl;
}


void ReadingroomBookConsole::printNotExistReservationMsg() {
	cout << "아직 예약하지 않았습니다." << endl;
}

void ReadingroomBookConsole::printCancelCompleteMsg() {
	cout << "예약을 성공적으로 취소했습니다." << endl;
}

void ReadingroomBookConsole::showSeats(vector<ReadingroomBookReservation*>& reservations, string id) {
	int num = 1;
	for (auto& reservation : reservations) {
		if (reservation->getID() == id) {
			cout << num << "번: " << reservation->getStartTime() << "시 ~ " << reservation->getEndTime() << "시 까지 예약하셨습니다." << endl;
		}
		num++;
	}
}

void ReadingroomBookConsole::showStat(int male, int female) {
	cout << "[ 남성 예약 횟수: " << male << " ]" << endl;
	cout << "[ 여성 예약 횟수: " << female << " ]" << endl;
}

int ReadingroomBookConsole::selectMenu() {
	cout << "[ 1: 예약하기   2: 취소하기   3: 예약내역   4: 통계   5: 종료 ]" << endl;
	cout << "메뉴를 선택하세요. >> ";
	return getInt();
}
