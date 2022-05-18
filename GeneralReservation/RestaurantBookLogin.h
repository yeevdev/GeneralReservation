#pragma once
#include "Login.h"
class RestaurantBookLogin : public Login {
public:
	RestaurantBookLogin(UserManager*);

private:
	bool signIn();
	void signUp();

public:
	void login();
};

