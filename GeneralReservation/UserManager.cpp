#pragma once
#include "UserManager.h"


UserManager::~UserManager() {
	for (auto& user : this->users) {
		User* pUser = user.second;
		delete pUser;
	}

	this->users.clear();
}

void UserManager::addUser(User* pUser) {
	this->users.insert({ pUser->getID(), pUser});
}

void UserManager::removeUser(User* pUser) {
	string id = pUser->getID();
	delete pUser;
	this->users.erase(id);
}

User& UserManager::getUser(string id) {
	User* pUser = this->users.find(id)->second;
	return *pUser;
}

bool UserManager::isUserExist(string id) {
	if (users.find(id) != users.end()) {
		return true;
	}
	else {
		return false;
	}
}
