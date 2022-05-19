#include "ReadingroomBookLogin.h"
#include "Console.h"
#include "ReadingroomBookConsole.h"
#include "ReadingroomBookLogin.h"
#include "ReadingroomBookUser.h"

ReadingroomBookLogin::ReadingroomBookLogin(UserManager* pManager) : Login(pManager) {
}

bool ReadingroomBookLogin::signIn() {
	string id, password;

	id = Console::getID();
	if (!this->pMyManager->isUserExist(id)) {
			// �������� �ʴ� ID�� ���(ȸ������ �ź�) false ��ȯ
		return false;
	}

	// ���� �ٷ�� �ִ� ����
	ReadingroomBookUser& thisUser = (ReadingroomBookUser&)this->pMyManager->getUser(id);

	if (!thisUser.isSet()) {
		if (Console::selectLoginSignUp()) {
			// ȸ���������� �̵�
			throw TRY_SIGNUP;
		}
		else {
			return false;
		}
	}

	password = Console::getPASSWORD();

	

	if (thisUser.isCorrectPassword(password)) {
		// ID, ��й�ȣ ��ġ
		this->pMyUser = &thisUser;
		return true;
	}
	else {
		// ID, ��й�ȣ ����ġ
		return false;
	}
}

void ReadingroomBookLogin::signUp() {
	try {
		Console::printLoginSignUpMsg();

		string id, password, name;

		id = Console::getID();
		if (!this->pMyManager->isUserExist(id)) {
			// �̹� �����ϴ� ���̵�
			throw INVALID_LOGIN;
		}
		else {
			ReadingroomBookUser& thisUser = (ReadingroomBookUser&)this->pMyManager->getUser(id);
			if (thisUser.isSet()) {
				throw ALREADY_EXIST;
			}
		}

		password = Console::getPASSWORD();

		int age = ReadingroomBookConsole::getAge();
		if (age <= 13) {
			throw TOO_YOUNG;
		}

		string gender = ReadingroomBookConsole::getGender();

		//name = Console::getName();

		//ReadingroomBookUser* pNewUser = new ReadingroomBookUser(id, password, name);
		//this->pMyManager->addUser((User*)pNewUser);

		ReadingroomBookUser& thisUser = (ReadingroomBookUser&)this->pMyManager->getUser(id);
		thisUser.setPASSWORD(password);
		thisUser.setAge(age);
		thisUser.setGender(gender);

		Console::clear();
		Console::printLoginSignUpCompleteMsg();
	}
	catch (LoginError e) {
		if (e == ALREADY_EXIST) {
			Console::printLoginAlreadyIDExistMsg();
			return signUp();
		}
	}
}

void ReadingroomBookLogin::login() {
	try {
		ReadingroomBookConsole::printLoginStartMsg();

		bool loginSuccess = signIn();
		if (loginSuccess) {
			Console::clear();
			Console::printLoginCompleteMsg(this->pMyUser->getName());
		}
		else {
			throw INVALID_LOGIN;
		}
	}
	catch (LoginError e) {
		if (e == TRY_SIGNUP) {
			signUp();
			return login();
		}
		else if (e == INVALID_LOGIN) {

			Console::printLoginFailMsg();
			return login();
		}
	}
}
