#include "RestaurantBookConsole.h"


void tempPrint(int num1, int num2, string a, string b, int c, int d) {
	string newC, newD;
	newC = to_string(c);
	newD = to_string(d);
	string num11 = to_string(num1);
	string num22 = to_string(num2);

	cout << "┌─────────────┐     ┌─────────────┐" << endl;
	cout << "│  " + num11 + "번 테이블 │     │  " + num22 + "번 테이블 │" << endl;
	cout << "│   [ " + newC + "인석 ] │     │   [ " + newD + "인석 ] │" << endl;
	cout << "│   " + a + "  │     │   " + b + "  │" << endl;
	cout << "└─────────────┘     └─────────────┘" << endl;
}

int RestaurantBookConsole::getAge() {
	cout << "나이를 입력하세요. >> ";
	return getInt();
}

int RestaurantBookConsole::getPeopleNum() {
	cout << "인원수를 입력해주세요. >> ";
	int result = getInt();
	if (result > 6) {
		cout << "6명이 넘는 인원수는 입장할 수 없습니다.";
		return getPeopleNum();
	}
	return result;
}

void RestaurantBookConsole::printTooYoungAge() {
	cout << "7세 이하의 어린이는 등록할 수 없습니다." << endl;
}

void RestaurantBookConsole::printWelcomeMsg() {
	cout << "***** 홍익식당에 오신 것을 환영합니다. *****" << endl;
}

void RestaurantBookConsole::printExitMsg() {
	cout << "***** 식당예약 프로그램에서 로그아웃 합니다." << endl;
}

void RestaurantBookConsole::printReserveCompleteMsg() {
	cout << "예약이 완료되었습니다." << endl;
}

void RestaurantBookConsole::printTables(vector<RestaurantBookTable*>& tables, int count) {
	string arr[6];
	int i = 0;
	for (auto& element : tables) {
		if (element->isReserved() || (i == 1 || i == 3 || i == 5) || element->getSize() < count) {
			arr[i] = "예약불가";
		}
		else {
			arr[i] = "예약가능";
		}
		i++;
	}

	tempPrint(1, 2, arr[0], arr[1], tables[0]->getSize(), tables[1]->getSize());
	tempPrint(3, 4, arr[2], arr[3], tables[2]->getSize(), tables[3]->getSize());
	tempPrint(5, 6, arr[4], arr[5], tables[4]->getSize(), tables[5]->getSize());
}

void RestaurantBookConsole::printNotExistReservationMsg() {
	cout << "예약이나 대기가 없습니다." << endl;
}

void RestaurantBookConsole::printCancelCompleteMsg() {
	cout << "식당 예약을 취소했습니다." << endl;
}

void RestaurantBookConsole::printShowReservation(RestaurantBookReservation& reservation) {
	cout << "[ 현재 " << reservation.getTable().getTableNum() << "번 테이블에 " << reservation.getCustomerNum() << "명 예약하셨습니다. ]" << endl;
}

void RestaurantBookConsole::printIsEatingMsg() {
	cout << "[ 손님께선 이미 식사중입니다. ]" << endl;
}

void RestaurantBookConsole::printNotExistWaitingMsg() {
	cout << "[ 현재 대기가 없습니다. ]" << endl;
}

void RestaurantBookConsole::printWaitingMsg(vector<string>& waitings) {
	cout << "[ 현재 대기가 " << waitings.size() << "팀 있습니다. ]" << endl;
}

void RestaurantBookConsole::printNowWaitingMsg(vector<string>& waitings, int num) {
	cout << "[ 현재 대기가 " << waitings.size() << "팀 있고, 손님은 대기순번 " << num <<  "번 입니다. ]" << endl;
}

void RestaurantBookConsole::printNotEating() {
	cout << "현재 식사중이 아닙니다." << endl;
}

void RestaurantBookConsole::printStat() {
	cout << "[ 테이블별 예약 누적 횟수 ]" << endl;
}

void RestaurantBookConsole::printStatTable(int tableNum, int count) {
	cout << tableNum << "번 테이블: " << count << "번" << endl;
}

int RestaurantBookConsole::selectMenu() {
	cout << "[ 1: 예약하기   2: 취소하기   3: Walk-In   4: 예약/대기내역   5: Walk-In 종료   6: 통계   7: 종료 ]" << endl;
	cout << "메뉴를 선택하세요 >> ";

	int result = getInt();
	if (result < 1 || result > 7) {
		cout << "올바르지 않은 입력입니다. 다시 입력해 주십시오." << endl;
		return selectMenu();
	}

	return result;
}

int RestaurantBookConsole::selectTable(vector<RestaurantBookTable*>& tables, int num) {
	cout << "[ 2번, 4번, 6번 테이블은 Walk-In 손님 전용으로 예약이 불가합니다. ]" << endl;
	cout << "[ 1번, 3번, 5번 테이블은 이미 예약이 되어있는 경우 예약이 불가합니다. ]" << endl;
	cout << "[ 인원수를 수용할 수 없는 테이블은 예약이 불가합니다. ]" << endl;

	printTables(tables, num);
	cout << "테이블을 선택하세요. >> ";
	int result = getInt();
	bool canReserve = !(tables[result - 1]->isReserved() || (result == 2 || result == 4 || result == 6) || tables[result - 1]->getSize() < num);
	if (!canReserve) {
		cout << "해당 테이블은 예약할 수 없습니다." << endl;
		printENDL();
		return selectTable(tables, num);
	}
	return result;
}
