#pragma once

#include <string>


using namespace std;

class User {
public:
	User(string, string, string);

protected:
	string id;
	string password;
	string name;

public:
	string getID();
	string getName();

	bool isCorrectPassword(string);
};

