#include "RestaurantBookConsole.h"


void tempPrint(int num1, int num2, string a, string b, int c, int d) {
	string newC, newD;
	newC = to_string(c);
	newD = to_string(d);
	string num11 = to_string(num1);
	string num22 = to_string(num2);

	cout << "������������������������������     ������������������������������" << endl;
	cout << "��  " + num11 + "�� ���̺� ��     ��  " + num22 + "�� ���̺� ��" << endl;
	cout << "��   [ " + newC + "�μ� ] ��     ��   [ " + newD + "�μ� ] ��" << endl;
	cout << "��   " + a + "  ��     ��   " + b + "  ��" << endl;
	cout << "������������������������������     ������������������������������" << endl;
}

int RestaurantBookConsole::getAge() {
	cout << "���̸� �Է��ϼ���. >> ";
	return getInt();
}

int RestaurantBookConsole::getPeopleNum() {
	cout << "�ο����� �Է����ּ���. >> ";
	int result = getInt();
	if (result > 6) {
		cout << "6���� �Ѵ� �ο����� ������ �� �����ϴ�.";
		return getPeopleNum();
	}
	return result;
}

void RestaurantBookConsole::printTooYoungAge() {
	cout << "7�� ������ ��̴� ����� �� �����ϴ�." << endl;
}

void RestaurantBookConsole::printWelcomeMsg() {
	cout << "***** ȫ�ͽĴ翡 ���� ���� ȯ���մϴ�. *****" << endl;
}

void RestaurantBookConsole::printExitMsg() {
	cout << "***** �Ĵ翹�� ���α׷����� �α׾ƿ� �մϴ�." << endl;
}

void RestaurantBookConsole::printReserveCompleteMsg() {
	cout << "������ �Ϸ�Ǿ����ϴ�." << endl;
}

void RestaurantBookConsole::printTables(vector<RestaurantBookTable*>& tables, int count) {
	string arr[6];
	int i = 0;
	for (auto& element : tables) {
		if (element->isReserved() || (i == 1 || i == 3 || i == 5) || element->getSize() < count) {
			arr[i] = "����Ұ�";
		}
		else {
			arr[i] = "���డ��";
		}
		i++;
	}

	tempPrint(1, 2, arr[0], arr[1], tables[0]->getSize(), tables[1]->getSize());
	tempPrint(3, 4, arr[2], arr[3], tables[2]->getSize(), tables[3]->getSize());
	tempPrint(5, 6, arr[4], arr[5], tables[4]->getSize(), tables[5]->getSize());
}

void RestaurantBookConsole::printNotExistReservationMsg() {
	cout << "�����̳� ��Ⱑ �����ϴ�." << endl;
}

void RestaurantBookConsole::printCancelCompleteMsg() {
	cout << "�Ĵ� ������ ����߽��ϴ�." << endl;
}

void RestaurantBookConsole::printShowReservation(RestaurantBookReservation& reservation) {
	cout << "[ ���� " << reservation.getTable().getTableNum() << "�� ���̺� " << reservation.getCustomerNum() << "�� �����ϼ̽��ϴ�. ]" << endl;
}

void RestaurantBookConsole::printIsEatingMsg() {
	cout << "[ �մԲ��� �̹� �Ļ����Դϴ�. ]" << endl;
}

void RestaurantBookConsole::printNotExistWaitingMsg() {
	cout << "[ ���� ��Ⱑ �����ϴ�. ]" << endl;
}

void RestaurantBookConsole::printWaitingMsg(vector<string>& waitings) {
	cout << "[ ���� ��Ⱑ " << waitings.size() << "�� �ֽ��ϴ�. ]" << endl;
}

void RestaurantBookConsole::printNowWaitingMsg(vector<string>& waitings, int num) {
	cout << "[ ���� ��Ⱑ " << waitings.size() << "�� �ְ�, �մ��� ������ " << num <<  "�� �Դϴ�. ]" << endl;
}

void RestaurantBookConsole::printNotEating() {
	cout << "���� �Ļ����� �ƴմϴ�." << endl;
}

void RestaurantBookConsole::printStat() {
	cout << "[ ���̺� ���� ���� Ƚ�� ]" << endl;
}

void RestaurantBookConsole::printStatTable(int tableNum, int count) {
	cout << tableNum << "�� ���̺�: " << count << "��" << endl;
}

int RestaurantBookConsole::selectMenu() {
	cout << "[ 1: �����ϱ�   2: ����ϱ�   3: Walk-In   4: ����/��⳻��   5: Walk-In ����   6: ���   7: ���� ]" << endl;
	cout << "�޴��� �����ϼ��� >> ";

	int result = getInt();
	if (result < 1 || result > 7) {
		cout << "�ùٸ��� ���� �Է��Դϴ�. �ٽ� �Է��� �ֽʽÿ�." << endl;
		return selectMenu();
	}

	return result;
}

int RestaurantBookConsole::selectTable(vector<RestaurantBookTable*>& tables, int num) {
	cout << "[ 2��, 4��, 6�� ���̺��� Walk-In �մ� �������� ������ �Ұ��մϴ�. ]" << endl;
	cout << "[ 1��, 3��, 5�� ���̺��� �̹� ������ �Ǿ��ִ� ��� ������ �Ұ��մϴ�. ]" << endl;
	cout << "[ �ο����� ������ �� ���� ���̺��� ������ �Ұ��մϴ�. ]" << endl;

	printTables(tables, num);
	cout << "���̺��� �����ϼ���. >> ";
	int result = getInt();
	bool canReserve = !(tables[result - 1]->isReserved() || (result == 2 || result == 4 || result == 6) || tables[result - 1]->getSize() < num);
	if (!canReserve) {
		cout << "�ش� ���̺��� ������ �� �����ϴ�." << endl;
		printENDL();
		return selectTable(tables, num);
	}
	return result;
}
