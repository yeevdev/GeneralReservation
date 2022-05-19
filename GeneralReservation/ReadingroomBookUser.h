#pragma once
#include "User.h"
#include "Console.h"
class ReadingroomBookUser : public User {
public:
	ReadingroomBookUser(string, string, string);

private:
	int age;
	string gender;

public:
	void setAge(int);
	int getAge();
	void setPASSWORD(string);
	bool isSet();
	void setGender(string);
	string getGender();
};

