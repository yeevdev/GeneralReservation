#pragma once
#include "AirlineBookConsole.h"
#include "AirlineBookFlight.h"

void tempPrint1(int num) {
	for (int i = 0; i < num; i++) {
		if (i == 0) {
			cout << "┌";
			continue;
		}
		else if (i == num - 1) {
			
			cout << "┐";
			continue;
		}
		else {
			cout << "─";
		}
	}
}

void tempPrint2(int num) {
	for (int i = 0; i < num; i++) {
		if (i == 0) {
			cout << "└";
			continue;
		}
		else if (i == num - 1) {
			cout << "┘";
			continue;
		}
		else {
			cout << "─";
		}
	}
}

void AirlineBookConsole::printWelcomeMsg() {
	cout << "***** 홍익항공에 오신 것을 환영합니다. *****" << endl;
}

void AirlineBookConsole::printExitMsg() {
	cout << "***** 홍익항공 예약프로그램에서 로그아웃 합니다. *****" << endl;
}

void AirlineBookConsole::printUserData(AirlineBookUser& user) {
	cout << "[ 현재 잔액: " << user.getMoney() << "원    보유 마일리지: " << user.getMileage() << "km ]" << endl;
}

void AirlineBookConsole::printSameAirportMsg() {
	cout << "공항을 잘못 선택하셨습니다. 다시 선택해 주십시오." << endl;
}

void AirlineBookConsole::printFlight(AirlineBookFlight& flight, int num) {
	tempPrint1(42);
	printENDL();

	cout << "│";
	cout << "       출발    도착     출발날짜:  " << flight.getDate() << " ";
	cout << "│";
	printENDL();

	cout << "│";

	cout << " " << getFormattedInt(num) << ":   " + flight.getDepartureAirport() + " -> " + flight.getArrivalAirport()
		+ "     출발시각:  " << getFormattedInt(flight.getDepartureTime()) << ":00";

	cout << "│";
	printENDL();
	tempPrint2(42);
	printENDL();
}

void AirlineBookConsole::printSeats(AirlineBookFlight& flight, string id) {
	printENDL();
	cout << "[ □: 예약 가능한 좌석, ■: 이미 예약된 좌석 ]" << endl;
	cout << "[ " << ANSI_COLOR_YELLOW << "노란색" << ANSI_COLOR_RESET << "은 비지니스석입니다. ]" << endl;
	printENDL();

	tempPrint1(50); cout << " " << endl;
	//printENDL();
	cout << "│"; cout << "│";

	for (int i = 0; i < 8; i++) {
		string status = "□";
		if (flight.getSeat(i + 1).getSeatClass() == BUSINESS) {
			cout << ANSI_COLOR_YELLOW;
		}
		if (flight.getSeat(i + 1).getCustomerID() == id) {
			cout << ANSI_COLOR_GREEN;
		}
		if (flight.getSeat(i + 1).isReserved()) {
			status = "■";
		}

		cout << "  " << status << ANSI_COLOR_RESET << "  ";
	}

	cout << "│";
	printENDL();

	cout << "│";
	for (int i = 0; i < 8; i++) {
		cout << "   " << i + 1 << "  ";
	}
	cout << "│";
	printENDL();

	tempPrint2(50);
	printENDL();
}

void AirlineBookConsole::printNotEnoughMoney() {
	cout << "잔액이 충분하지 않습니다. 좌석 선택으로 돌아갑니다." << endl;
}

void AirlineBookConsole::printReserveCompleteMsg() {
	cout << "해당 항공권을 성공적으로 예매했습니다." << endl;
}

void AirlineBookConsole::printRoundTicketMsg() {
	cout << "왕복권의 예매를 시작합니다." << endl;
}

void AirlineBookConsole::printNotExistTicket() {
	cout << "아직 항공권을 예매하지 않으셨습니다." << endl;
}

void AirlineBookConsole::printStatBookCount(AirlineBookUser& user) {
	cout << "[ 현재까지 예약한 횟수: " << user.getBookCount() << "회 ]" << endl;
}

void AirlineBookConsole::printStatSeatCount(vector<AirlineBookTicket*>& tickets) {
	cout << "[ 좌석별 예약 회수 ]" << endl;

	int bookCount[8];
	for (auto& element : bookCount) {
		element = 0;
	} //초기화

	for (auto& ticket : tickets) {
		bookCount[ticket->getSeatNum() - 1]++;
	}

	for (int i = 0; i < 8; i++) {
		cout << i + 1 << "번 좌석: " << bookCount[i] << "회" << endl;
	}
}

int AirlineBookConsole::selectMenu() {
	cout << "[ 1: 예약하기   2: 취소하기   3: 예약내역   4: 통계   5: 종료 ]" << endl;
	cout << "메뉴를 선택하세요 >> ";

	int result = getInt();
	if (result < 1 || result > 5) {
		cout << "올바르지 않은 입력입니다. 다시 입력해 주십시오." << endl;
		return selectMenu();
	}

	return result;
}

int AirlineBookConsole::selectFlight(vector<AirlineBookFlight*>& flights) {
	cout << "검색된 항공편입니다." << endl;
	for (int i = 0; i < flights.size(); i++) {
		printFlight(*flights[i], i + 1);
	}
	cout << "항공편을 선택해주세요.(숫자) >> ";
	return getInt();
}

int AirlineBookConsole::selectSeat(AirlineBookFlight& flight, int money) {
	printENDL();
	cout << "[ □: 예약 가능한 좌석, ■: 이미 예약된 좌석, ▩: 잔액부족으로 인한 예약불가능한 좌석 ]" << endl;
	cout << "[ " << ANSI_COLOR_YELLOW << "노란색" << ANSI_COLOR_RESET << "은 비지니스석입니다. ]" << endl;
	printENDL();

	tempPrint1(50); cout << " " << endl;
	//printENDL();
	cout << "│"; cout << "│";

	for (int i = 0; i < 8; i++) {
		string status = "□";
		if (flight.getSeat(i + 1).getSeatClass() == BUSINESS) {
			cout << ANSI_COLOR_YELLOW;
		}
		if (flight.getSeat(i + 1).isReserved()) {
			status = "■";
		}
		else if (money < flight.getSeat(i + 1).getPrice()) {
			status = "▩";
		}

		cout << "  " << status << ANSI_COLOR_RESET << "  ";
	}

	cout << "│";
	printENDL();

	cout << "│";
	for (int i = 0; i < 8; i++) {
		cout << "   " << i + 1 << "  ";
	}
	cout << "│";
	printENDL();

	tempPrint2(50);
	printENDL();

	cout << "예약하려는 좌석의 번호를 입력하세요. >>";
	return getInt();
}

int AirlineBookConsole::selectCancelTicket(vector<AirlineBookTicket*>& tickets) {
	cout << "예약하신 항공권의 목록입니다." << endl;
	int i = 0;
	for (auto& ticket : tickets) {
		AirlineBookFlight& flight = ticket->getFlight();
		tempPrint1(42);
		printENDL();

		cout << "│";
		cout << "       출발    도착     출발날짜:  " << flight.getDate() << " ";
		cout << "│";
		printENDL();

		cout << "│";

		cout << " " << getFormattedInt(i + 1) << ":   " + flight.getDepartureAirport() + " -> " + flight.getArrivalAirport()
			+ "     출발시각:  " << getFormattedInt(flight.getDepartureTime()) << ":00";

		cout << "│";
		printENDL();
		tempPrint2(42);
		printENDL();

		i++;
	}
	cout << "취소할 항공권을 선택하세요. >> ";
	return getInt();
}

int AirlineBookConsole::selectShowTicket(vector<AirlineBookTicket*>& tickets) {
	cout << "예약하신 항공권의 목록입니다." << endl;
	int i = 0;
	for (auto& ticket : tickets) {
		AirlineBookFlight& flight = ticket->getFlight();
		tempPrint1(42);
		printENDL();

		cout << "│";
		cout << "       출발    도착     출발날짜:  " << flight.getDate() << " ";
		cout << "│";
		printENDL();

		cout << "│";

		cout << " " << getFormattedInt(i+1) << ":   " + flight.getDepartureAirport() + " -> " + flight.getArrivalAirport()
			+ "     출발시각:  " << getFormattedInt(flight.getDepartureTime()) << ":00";

		cout << "│";
		printENDL();
		tempPrint2(42);
		printENDL();

		i++;
	}
	cout << "[ 0: 메뉴로 돌아가기   1~: 해당 항공권 확인하기 ]" << endl;
	cout << "선택해주세요. >> ";
	return getInt();
}

string AirlineBookConsole::selectDate(vector<string>& dates) {
	cout << "[ 출발일 : 5/11  5/12  5/13  5/14  5/15  5/16  5/17 ]" << endl;
	cout << "출발일을 선택하세요. >> ";

	string result = getString();
	
	if (find(dates.begin(), dates.end(), result) != dates.end()) {
		return result;
	}
	else {
		cout << "올바르지 않은 입력입니다. 다시 입력해 주십시오." << endl;
		return selectDate(dates);
	}
}

string AirlineBookConsole::selectDepartureAirport() {
	cout << "[ 공항목록: 인천, 김포, 김해, 청주, 제주 ]" << endl;
	while (true) {
		cout << "출발 공항을 선택하세요 >> ";
		string result = getString();
		if (result == "인천" || result == "김포" || result == "김해" || result == "청주" || result == "제주") {
			return result;
		}
		else {
			cout << "해당 공항을 찾을 수 없습니다. 다시 입력해주십시오." << endl;
		}
	}
}

string AirlineBookConsole::selectArrivalAirport() {
	cout << "[ 공항목록: 인천, 김포, 김해, 청주, 제주 ]" << endl;
	while (true) {
		cout << "도착 공항을 선택하세요 >> ";
		string result = getString();
		if (result == "인천" || result == "김포" || result == "김해" || result == "청주" || result == "제주") {
			return result;
		}
		else {
			cout << "해당 공항을 찾을 수 없습니다. 다시 입력해주십시오." << endl;
		}
	}
}

bool AirlineBookConsole::selectRoundTicket() {
	cout << "왕복권으로 하시겠습니까? (Y / N) >> ";
	return getYesOrNo();
}
