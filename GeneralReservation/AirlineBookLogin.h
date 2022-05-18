#pragma once

#include "Login.h"
#include "AirlineBookUser.h"


class AirlineBookLogin : public Login {
public:
	AirlineBookLogin(UserManager*);

private:
	bool signIn();
	void signUp();
	
public:
	void login();

};

