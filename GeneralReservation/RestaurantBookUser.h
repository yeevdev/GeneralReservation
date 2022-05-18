#pragma once
#include "Console.h"
#include "User.h"

class RestaurantBookUser : public User {
public:
	RestaurantBookUser(string, string, string, int);
	
private:
	int age;
	bool eating;

public:
	int getAge();
	bool isEating();
	void setEating(bool);
};

