#pragma once
#include "AirlineBookConsole.h"
#include "AirlineBookFlight.h"

void tempPrint1(int num) {
	for (int i = 0; i < num; i++) {
		if (i == 0) {
			cout << "��";
			continue;
		}
		else if (i == num - 1) {
			
			cout << "��";
			continue;
		}
		else {
			cout << "��";
		}
	}
}

void tempPrint2(int num) {
	for (int i = 0; i < num; i++) {
		if (i == 0) {
			cout << "��";
			continue;
		}
		else if (i == num - 1) {
			cout << "��";
			continue;
		}
		else {
			cout << "��";
		}
	}
}

void AirlineBookConsole::printWelcomeMsg() {
	cout << "***** ȫ���װ��� ���� ���� ȯ���մϴ�. *****" << endl;
}

void AirlineBookConsole::printExitMsg() {
	cout << "***** ȫ���װ� �������α׷����� �α׾ƿ� �մϴ�. *****" << endl;
}

void AirlineBookConsole::printUserData(AirlineBookUser& user) {
	cout << "[ ���� �ܾ�: " << user.getMoney() << "��    ���� ���ϸ���: " << user.getMileage() << "km ]" << endl;
}

void AirlineBookConsole::printSameAirportMsg() {
	cout << "������ �߸� �����ϼ̽��ϴ�. �ٽ� ������ �ֽʽÿ�." << endl;
}

void AirlineBookConsole::printFlight(AirlineBookFlight& flight, int num) {
	tempPrint1(42);
	printENDL();

	cout << "��";
	cout << "       ���    ����     ��߳�¥:  " << flight.getDate() << " ";
	cout << "��";
	printENDL();

	cout << "��";

	cout << " " << getFormattedInt(num) << ":   " + flight.getDepartureAirport() + " -> " + flight.getArrivalAirport()
		+ "     ��߽ð�:  " << getFormattedInt(flight.getDepartureTime()) << ":00";

	cout << "��";
	printENDL();
	tempPrint2(42);
	printENDL();
}

void AirlineBookConsole::printSeats(AirlineBookFlight& flight, string id) {
	printENDL();
	cout << "[ ��: ���� ������ �¼�, ��: �̹� ����� �¼� ]" << endl;
	cout << "[ " << ANSI_COLOR_YELLOW << "�����" << ANSI_COLOR_RESET << "�� �����Ͻ����Դϴ�. ]" << endl;
	printENDL();

	tempPrint1(50); cout << " " << endl;
	//printENDL();
	cout << "��"; cout << "��";

	for (int i = 0; i < 8; i++) {
		string status = "��";
		if (flight.getSeat(i + 1).getSeatClass() == BUSINESS) {
			cout << ANSI_COLOR_YELLOW;
		}
		if (flight.getSeat(i + 1).getCustomerID() == id) {
			cout << ANSI_COLOR_GREEN;
		}
		if (flight.getSeat(i + 1).isReserved()) {
			status = "��";
		}

		cout << "  " << status << ANSI_COLOR_RESET << "  ";
	}

	cout << "��";
	printENDL();

	cout << "��";
	for (int i = 0; i < 8; i++) {
		cout << "   " << i + 1 << "  ";
	}
	cout << "��";
	printENDL();

	tempPrint2(50);
	printENDL();
}

void AirlineBookConsole::printNotEnoughMoney() {
	cout << "�ܾ��� ������� �ʽ��ϴ�. �¼� �������� ���ư��ϴ�." << endl;
}

void AirlineBookConsole::printReserveCompleteMsg() {
	cout << "�ش� �װ����� ���������� �����߽��ϴ�." << endl;
}

void AirlineBookConsole::printRoundTicketMsg() {
	cout << "�պ����� ���Ÿ� �����մϴ�." << endl;
}

void AirlineBookConsole::printNotExistTicket() {
	cout << "���� �װ����� �������� �����̽��ϴ�." << endl;
}

void AirlineBookConsole::printStatBookCount(AirlineBookUser& user) {
	cout << "[ ������� ������ Ƚ��: " << user.getBookCount() << "ȸ ]" << endl;
}

void AirlineBookConsole::printStatSeatCount(vector<AirlineBookTicket*>& tickets) {
	cout << "[ �¼��� ���� ȸ�� ]" << endl;

	int bookCount[8];
	for (auto& element : bookCount) {
		element = 0;
	} //�ʱ�ȭ

	for (auto& ticket : tickets) {
		bookCount[ticket->getSeatNum() - 1]++;
	}

	for (int i = 0; i < 8; i++) {
		cout << i + 1 << "�� �¼�: " << bookCount[i] << "ȸ" << endl;
	}
}

int AirlineBookConsole::selectMenu() {
	cout << "[ 1: �����ϱ�   2: ����ϱ�   3: ���೻��   4: ���   5: ���� ]" << endl;
	cout << "�޴��� �����ϼ��� >> ";

	int result = getInt();
	if (result < 1 || result > 5) {
		cout << "�ùٸ��� ���� �Է��Դϴ�. �ٽ� �Է��� �ֽʽÿ�." << endl;
		return selectMenu();
	}

	return result;
}

int AirlineBookConsole::selectFlight(vector<AirlineBookFlight*>& flights) {
	cout << "�˻��� �װ����Դϴ�." << endl;
	for (int i = 0; i < flights.size(); i++) {
		printFlight(*flights[i], i + 1);
	}
	cout << "�װ����� �������ּ���.(����) >> ";
	return getInt();
}

int AirlineBookConsole::selectSeat(AirlineBookFlight& flight, int money) {
	printENDL();
	cout << "[ ��: ���� ������ �¼�, ��: �̹� ����� �¼�, ��: �ܾ׺������� ���� ����Ұ����� �¼� ]" << endl;
	cout << "[ " << ANSI_COLOR_YELLOW << "�����" << ANSI_COLOR_RESET << "�� �����Ͻ����Դϴ�. ]" << endl;
	printENDL();

	tempPrint1(50); cout << " " << endl;
	//printENDL();
	cout << "��"; cout << "��";

	for (int i = 0; i < 8; i++) {
		string status = "��";
		if (flight.getSeat(i + 1).getSeatClass() == BUSINESS) {
			cout << ANSI_COLOR_YELLOW;
		}
		if (flight.getSeat(i + 1).isReserved()) {
			status = "��";
		}
		else if (money < flight.getSeat(i + 1).getPrice()) {
			status = "��";
		}

		cout << "  " << status << ANSI_COLOR_RESET << "  ";
	}

	cout << "��";
	printENDL();

	cout << "��";
	for (int i = 0; i < 8; i++) {
		cout << "   " << i + 1 << "  ";
	}
	cout << "��";
	printENDL();

	tempPrint2(50);
	printENDL();

	cout << "�����Ϸ��� �¼��� ��ȣ�� �Է��ϼ���. >>";
	return getInt();
}

int AirlineBookConsole::selectCancelTicket(vector<AirlineBookTicket*>& tickets) {
	cout << "�����Ͻ� �װ����� ����Դϴ�." << endl;
	int i = 0;
	for (auto& ticket : tickets) {
		AirlineBookFlight& flight = ticket->getFlight();
		tempPrint1(42);
		printENDL();

		cout << "��";
		cout << "       ���    ����     ��߳�¥:  " << flight.getDate() << " ";
		cout << "��";
		printENDL();

		cout << "��";

		cout << " " << getFormattedInt(i + 1) << ":   " + flight.getDepartureAirport() + " -> " + flight.getArrivalAirport()
			+ "     ��߽ð�:  " << getFormattedInt(flight.getDepartureTime()) << ":00";

		cout << "��";
		printENDL();
		tempPrint2(42);
		printENDL();

		i++;
	}
	cout << "����� �װ����� �����ϼ���. >> ";
	return getInt();
}

int AirlineBookConsole::selectShowTicket(vector<AirlineBookTicket*>& tickets) {
	cout << "�����Ͻ� �װ����� ����Դϴ�." << endl;
	int i = 0;
	for (auto& ticket : tickets) {
		AirlineBookFlight& flight = ticket->getFlight();
		tempPrint1(42);
		printENDL();

		cout << "��";
		cout << "       ���    ����     ��߳�¥:  " << flight.getDate() << " ";
		cout << "��";
		printENDL();

		cout << "��";

		cout << " " << getFormattedInt(i+1) << ":   " + flight.getDepartureAirport() + " -> " + flight.getArrivalAirport()
			+ "     ��߽ð�:  " << getFormattedInt(flight.getDepartureTime()) << ":00";

		cout << "��";
		printENDL();
		tempPrint2(42);
		printENDL();

		i++;
	}
	cout << "[ 0: �޴��� ���ư���   1~: �ش� �װ��� Ȯ���ϱ� ]" << endl;
	cout << "�������ּ���. >> ";
	return getInt();
}

string AirlineBookConsole::selectDate(vector<string>& dates) {
	cout << "[ ����� : 5/11  5/12  5/13  5/14  5/15  5/16  5/17 ]" << endl;
	cout << "������� �����ϼ���. >> ";

	string result = getString();
	
	if (find(dates.begin(), dates.end(), result) != dates.end()) {
		return result;
	}
	else {
		cout << "�ùٸ��� ���� �Է��Դϴ�. �ٽ� �Է��� �ֽʽÿ�." << endl;
		return selectDate(dates);
	}
}

string AirlineBookConsole::selectDepartureAirport() {
	cout << "[ ���׸��: ��õ, ����, ����, û��, ���� ]" << endl;
	while (true) {
		cout << "��� ������ �����ϼ��� >> ";
		string result = getString();
		if (result == "��õ" || result == "����" || result == "����" || result == "û��" || result == "����") {
			return result;
		}
		else {
			cout << "�ش� ������ ã�� �� �����ϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
		}
	}
}

string AirlineBookConsole::selectArrivalAirport() {
	cout << "[ ���׸��: ��õ, ����, ����, û��, ���� ]" << endl;
	while (true) {
		cout << "���� ������ �����ϼ��� >> ";
		string result = getString();
		if (result == "��õ" || result == "����" || result == "����" || result == "û��" || result == "����") {
			return result;
		}
		else {
			cout << "�ش� ������ ã�� �� �����ϴ�. �ٽ� �Է����ֽʽÿ�." << endl;
		}
	}
}

bool AirlineBookConsole::selectRoundTicket() {
	cout << "�պ������� �Ͻðڽ��ϱ�? (Y / N) >> ";
	return getYesOrNo();
}
