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
		cin.ignore(256, '\n');  // ���� ����
		cout << "�ùٸ��� ���� �Է��Դϴ�." << endl;
		cout << "�ٽ� �Է��� �ֽʽÿ�. >> ";

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
		cout << "�ùٸ��� ���� �Է��Դϴ�." << endl;
		cout << "�ٽ� �Է��� �ֽʽÿ�. >> ";

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
	cout << "***** ���տ���ý����� �����մϴ�. *****" << endl;
	printENDL();
}

void Console::printExitMsg() {
	cout << "***** ���տ���ý����� �����մϴ�. *****" << endl;
	printENDL();
}

int Console::selectProgram() {
	cout << "[ 1: �װ��� ����   2: �Ĵ� ����   3: ������ ����   4: ���� ]" << endl;
	cout << "� ���񽺸� �̿��Ͻðڽ��ϱ�? >> ";
	
	int result;
	result = getInt();

	if (result < 1 || result > 4) {
		cout << "�ùٸ��� ���� �Է��Դϴ�. �ٽ� �Է��� �ֽʽÿ�." << endl;
		return selectProgram();
	}

	return result;
}

string Console::getID() {
	cout << "ID >> ";
	return getString();
}

string Console::getPASSWORD() {
	cout << "��й�ȣ >> ";
	return getString();
}

string Console::getName() {
	cout << "�̸� >> ";
	return getString();
}

bool Console::selectLoginSignUp() {
	cout << "��ϵ��� ���� ������Դϴ�. ȸ������ �Ͻðڽ��ϱ�? (Y / N) >> ";
	return getYesOrNo();
}

void Console::printLoginStartMsg() {
	cout << "�α����� �ʿ��մϴ�." << endl;
}

void Console::printLoginCompleteMsg(string name) {
	cout << "�α����� �Ϸ��߽��ϴ�. " << name << " �� ȯ���մϴ�!" << endl;
}

void Console::printLoginSignUpMsg() {
	cout << "ȸ�������� �����մϴ�. ����� ID�� ��й�ȣ�� �Է��� �ֽʽÿ�." << endl;
}

void Console::printLoginSignUpCompleteMsg() {
	cout << "ȸ�������� �Ϸ��߽��ϴ�. �ٽ� �α����� �ֽʽÿ�." << endl;
}

void Console::printLoginAlreadyIDExistMsg() {
	cout << "�̹� �����ϴ� ID�Դϴ�. �ٽ� ȸ�������� �ֽʽÿ�." << endl;
}

void Console::printLoginFailMsg() {
	cout << "�ùٸ��� ���� ID�� ��й�ȣ�� �Է��ϼ̽��ϴ�. �ٽ� �α����� �ֽʽÿ�." << endl;
}
