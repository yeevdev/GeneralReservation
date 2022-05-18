#pragma once

#include <map>
#include "User.h"


class UserManager {
public:
	virtual ~UserManager();

protected:
	map<string, User*> users;

public:
	void addUser(User*);
	void removeUser(User*);
	
	User& getUser(string);

	bool isUserExist(string);
};

