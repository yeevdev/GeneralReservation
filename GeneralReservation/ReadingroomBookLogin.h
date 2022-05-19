#pragma once
#include "Login.h"
class ReadingroomBookLogin : public Login {
public:
	ReadingroomBookLogin(UserManager*);

private:
	bool signIn();
	void signUp();

public:
	void login();
};

