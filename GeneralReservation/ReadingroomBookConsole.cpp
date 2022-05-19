#include "ReadingroomBookConsole.h"
#include "ReadingroomBookUser.h"
#include "ReadingroomBookReservation.h"

int ReadingroomBookConsole::getAge() {
	cout << "���̸� �Է��ϼ���. >> ";
	return getInt();
}

int ReadingroomBookConsole::getStartTime() {
	cout << "���۽ð��� �Է��ϼ���.(9,13, 17, 23 ���� �������� �Է��ϼ���.) >> ";

	return getInt();
}

int ReadingroomBookConsole::getEndTime() {
	cout << "����ð��� �Է��ϼ���.(9,13, 17, 23 ���� �������� �Է��ϼ���.) >> ";

	return getInt();
}

int ReadingroomBookConsole::getRow() {
	cout << "������ �¼��� ���� �Է��ϼ���. >> ";
	return getInt();
}

int ReadingroomBookConsole::getCulumn() {
	cout << "������ �¼��� ���� �Է��ϼ���. >> ";
	return getInt();
}

string ReadingroomBookConsole::getGender() {
	cout << "����(���� / ����) >> ";
	return getString();
}

void ReadingroomBookConsole::printLoginStartMsg() {
	cout << "�α����� �ʿ��մϴ�.  ID�� �����ȣ�Դϴ�." << endl;
}

void ReadingroomBookConsole::printWelcomeMsg() {
	cout << "***** ȫ�͵����ǿ� ���� ���� ȯ���մϴ�." << endl;
}

void ReadingroomBookConsole::printExitMsg() {
	cout << "***** �Ĵ� ���� ���α׷����� �α׾ƿ� �մϴ�. *****" << endl;
}

void ReadingroomBookConsole::printReserveMsg() {
	cout << "[ ��: ���� ������ �¼�, ��: �̹� ����� �¼� ]" << endl;
	cout << "[ " << ANSI_COLOR_CYAN << "��" << ANSI_COLOR_RESET << ": ���� ���༮, " << ANSI_COLOR_MAGENTA << "��" << ANSI_COLOR_RESET << ": ���� ���༮ ]" << endl;
	cout << "[ ��, ��, �翷�� �������� ���� �� �����ϴ�. ]" << endl;
	cout << "[ ������ �̿�ð��� 09:00 ~ 23:00 �Դϴ�. 1�ð� ������ ���డ���մϴ�. ]" << endl;
	cout << "[ ��) 9�� ����, 13�� ����  ->  09:00 ~ 13:00 �̿� ���� ]" << endl;
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
	cout << "     [01��] [02��] [03��] [04��] [05��] [06��] [07��] [08��] [09��] [10��] [11��] [12��] [13��] [14��] [15��]" << endl;
	ReadingroomBookUser& myUser = (ReadingroomBookUser&)manager.getUser(id);
	for (int i = 0; i < 15; i++) {
		cout << "[" << Console::getFormattedInt(i + 1) << "��] ";
		for (int j = 0; j < 15; j++) {
			ReadingroomBookSeat* thisSeat = seats[i][j];
			
			bool canReserve = true;
			string gender;
			for (int k = start - 9; k <= end - 10; k++) {
				if (thisSeat->isReserved(k+1) == true) {
					//cout << "�̰��� >" << thisSeat->isReserved(k + 1) << "?" << k << "< �̰���";
					string newnewid = thisSeat->getCustomerID(k + 1);

					ReadingroomBookUser& thisUser = (ReadingroomBookUser&)manager.getUser(newnewid);
					gender = thisUser.getGender();
					canReserve = false;
				}
			}
			if (!canReserve) {
				if (gender == "����") {
					cout << ANSI_COLOR_CYAN;
				}
				else {
					cout << ANSI_COLOR_MAGENTA;
				}
				cout << " ��    " << ANSI_COLOR_RESET;
			}
			else {
				cout << " ��    " << ANSI_COLOR_RESET;
			}
		}
		cout << endl;
	}
}

void ReadingroomBookConsole::printReserveCompleteMsg() {
	cout << "�ش� �¼��� �����߽��ϴ�." << endl;
}

void ReadingroomBookConsole::printReserveFailMsg() {
	cout << "�ش� �¼��� �����ϴµ� �����߽��ϴ�." << endl;
}


void ReadingroomBookConsole::printNotExistReservationMsg() {
	cout << "���� �������� �ʾҽ��ϴ�." << endl;
}

void ReadingroomBookConsole::printCancelCompleteMsg() {
	cout << "������ ���������� ����߽��ϴ�." << endl;
}

void ReadingroomBookConsole::showSeats(vector<ReadingroomBookReservation*>& reservations, string id) {
	int num = 1;
	for (auto& reservation : reservations) {
		if (reservation->getID() == id) {
			cout << num << "��: " << reservation->getStartTime() << "�� ~ " << reservation->getEndTime() << "�� ���� �����ϼ̽��ϴ�." << endl;
		}
		num++;
	}
}

void ReadingroomBookConsole::showStat(int male, int female) {
	cout << "[ ���� ���� Ƚ��: " << male << " ]" << endl;
	cout << "[ ���� ���� Ƚ��: " << female << " ]" << endl;
}

int ReadingroomBookConsole::selectMenu() {
	cout << "[ 1: �����ϱ�   2: ����ϱ�   3: ���೻��   4: ���   5: ���� ]" << endl;
	cout << "�޴��� �����ϼ���. >> ";
	return getInt();
}
