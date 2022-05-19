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
			// 존재하지 않는 ID일 경우(회원가입 거부) false 반환
		return false;
	}

	// 현재 다루고 있는 유저
	ReadingroomBookUser& thisUser = (ReadingroomBookUser&)this->pMyManager->getUser(id);

	if (!thisUser.isSet()) {
		if (Console::selectLoginSignUp()) {
			// 회원가입으로 이동
			throw TRY_SIGNUP;
		}
		else {
			return false;
		}
	}

	password = Console::getPASSWORD();

	

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

void ReadingroomBookLogin::signUp() {
	try {
		Console::printLoginSignUpMsg();

		string id, password, name;

		id = Console::getID();
		if (!this->pMyManager->isUserExist(id)) {
			// 이미 존재하는 아이디
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
