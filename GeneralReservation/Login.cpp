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
			// 회원가입으로 이동
			throw TRY_SIGNUP;
		}
		else {
			// 존재하지 않는 ID일 경우(회원가입 거부) false 반환
			return false;
		}
	}
	
	password = Console::getPASSWORD();

	// 현재 다루고 있는 유저
	User& thisUser = this->pMyManager->getUser(id);

	if (thisUser.isCorrectPassword(password)) {
		// ID, 비밀번호 일치
		this->pMyUser = &thisUser;
		return true;
	}
	else {
		// ID, 비밀번호 불일치
		return false;
	}
}

void Login::signUp() {
	try {
		Console::printLoginSignUpMsg();

		string id, password, name;

		id = Console::getID();
		if (this->pMyManager->isUserExist(id)) {
			// 이미 존재하는 아이디
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
