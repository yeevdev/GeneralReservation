#pragma once
#include "User.h"


User::User(string id, string password, string name) {
	this->id = id;
	this->password = password;
	this->name = name;
}

string User::getID() {
	return this->id;
}

string User::getName() {
	return this->name;
}

bool User::isCorrectPassword(string password) {
	return (this->password == password);
}
