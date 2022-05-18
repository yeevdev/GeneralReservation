#pragma once
#include "Login.h"
#include "Console.h"


Login::Login(UserManager* manager) {
	this->pMyManager = manager;
	this->pMyUser = nullptr;
}

bool Login::signIn() {
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

void Login::signUp() {
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

		User* pNewUser = new User(id, password, name);
		this->pMyManager->addUser(pNewUser);

		Console::printLoginSignUpCompleteMsg();
	}
	catch (LoginError e) {
		if (e == ALREADY_EXIST) {
			Console::printLoginAlreadyIDExistMsg();
			return signUp();
		}
	}
}

void Login::login() {
	try {
		Console::printLoginStartMsg();

		bool loginSuccess = signIn();
		if (loginSuccess) {
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

User& Login::getUser() {
	return *pMyUser;
}
