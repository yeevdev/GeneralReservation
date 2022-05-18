#include "RestaurantBookLogin.h"
#include "Console.h"
#include "RestaurantBookUser.h"
#include "RestaurantBookConsole.h"

RestaurantBookLogin::RestaurantBookLogin(UserManager* pManager) : Login(pManager) {
}

bool RestaurantBookLogin::signIn() {
	string id, password;

	id = Console::getID();
	if (!this->pMyManager->isUserExist(id)) {
		if (Console::selectLoginSignUp()) {
			// ȸ���������� �̵�
			throw TRY_SIGNUP;
		}
		else {
			// �������� �ʴ� ID�� ���(ȸ������ �ź�) false ��ȯ
			return false;
		}
	}

	password = Console::getPASSWORD();

	// ���� �ٷ�� �ִ� ����
	User& thisUser = this->pMyManager->getUser(id);

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

void RestaurantBookLogin::signUp() {
	try {
		Console::printLoginSignUpMsg();

		string id, password, name;

		id = Console::getID();
		if (this->pMyManager->isUserExist(id)) {
			// �̹� �����ϴ� ���̵�
			throw ALREADY_EXIST;
		}

		password = Console::getPASSWORD();
		name = Console::getName();

		int age = RestaurantBookConsole::getAge();
		if (age <= 7) {
			throw TOO_YOUNG;
		}

		RestaurantBookUser* pNewUser = new RestaurantBookUser(id, password, name, age);
		this->pMyManager->addUser((User*)pNewUser);

		Console::clear();
		Console::printLoginSignUpCompleteMsg();
	}
	catch (LoginError e) {
		if (e == ALREADY_EXIST) {
			Console::printLoginAlreadyIDExistMsg();
			return signUp();
		}
		else if (e == TOO_YOUNG) {
			RestaurantBookConsole::printTooYoungAge();
			return signUp();
		}
	}
}

void RestaurantBookLogin::login() {
	try {
		Console::printLoginStartMsg();

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
