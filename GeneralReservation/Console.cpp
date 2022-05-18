#include "Console.h"


void Console::printENDL() {
	cout << endl;
}

void Console::clear() {
	system("cls");
}

int Console::getInt() {
	try {
		int input;
		cin >> input;

		if (cin.fail()) {
			throw input;
		}

		return input;
	}
	catch (...) {
		cin.clear();
		cin.ignore(256, '\n');  // 버퍼 비우기
		cout << "올바르지 않은 입력입니다." << endl;
		cout << "다시 입력해 주십시오. >> ";

		return getInt();
	}
}

string Console::getString() {
	string input;
	cin >> input;

	return input;
}

bool Console::getYesOrNo() {
	try {
		string result = getString();

		if (result != "Y" && result != "y" && result != "N" && result != "n") {
			throw result;
		}

		if (result == "Y" || result == "y") {
			return true;
		}
		else {
			return false;
		}
	}
	catch (...) {
		cout << "올바르지 않은 입력입니다." << endl;
		cout << "다시 입력해 주십시오. >> ";

		return getYesOrNo();
	}
}

string Console::getFormattedInt(int num) {
	string result = to_string(num);
	if (num < 10) {
		result = "0" + result;
	}

	return result;
}

void Console::printStartMsg() {
	cout << "***** 종합예약시스템을 시작합니다. *****" << endl;
	printENDL();
}

void Console::printExitMsg() {
	cout << "***** 종합예약시스템을 종료합니다. *****" << endl;
	printENDL();
}

int Console::selectProgram() {
	cout << "[ 1: 항공권 예약   2: 식당 예약   3: 독서실 예약   4: 종료 ]" << endl;
	cout << "어떤 서비스를 이용하시겠습니까? >> ";
	
	int result;
	result = getInt();

	if (result < 1 || result > 4) {
		cout << "올바르지 않은 입력입니다. 다시 입력해 주십시오." << endl;
		return selectProgram();
	}

	return result;
}

string Console::getID() {
	cout << "ID >> ";
	return getString();
}

string Console::getPASSWORD() {
	cout << "비밀번호 >> ";
	return getString();
}

string Console::getName() {
	cout << "이름 >> ";
	return getString();
}

bool Console::selectLoginSignUp() {
	cout << "등록되지 않은 사용자입니다. 회원가입 하시겠습니까? (Y / N) >> ";
	return getYesOrNo();
}

void Console::printLoginStartMsg() {
	cout << "로그인이 필요합니다." << endl;
}

void Console::printLoginCompleteMsg(string name) {
	cout << "로그인을 완료했습니다. " << name << " 님 환영합니다!" << endl;
}

void Console::printLoginSignUpMsg() {
	cout << "회원가입을 시작합니다. 사용할 ID와 비밀번호를 입력해 주십시오." << endl;
}

void Console::printLoginSignUpCompleteMsg() {
	cout << "회원가입을 완료했습니다. 다시 로그인해 주십시오." << endl;
}

void Console::printLoginAlreadyIDExistMsg() {
	cout << "이미 존재하는 ID입니다. 다시 회원가입해 주십시오." << endl;
}

void Console::printLoginFailMsg() {
	cout << "올바르지 않은 ID나 비밀번호를 입력하셨습니다. 다시 로그인해 주십시오." << endl;
}
