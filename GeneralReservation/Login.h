#pragma once

#include "UserManager.h"


class Login {
public:
	Login(UserManager*);

protected:
	UserManager* pMyManager;
	User* pMyUser;
	 
public: 
	bool virtual signIn();
	void virtual signUp();
	void virtual login();
};

