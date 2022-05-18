#pragma once

#include "User.h"


class AirlineBookUser : public User {
public:
	AirlineBookUser(string, string, string);

private:
	int money;
	int mileage;
	int bookCount;

public:
	int getMoney();
	void setMoney(int);
	void addMoney(int);
	void subtractMoney(int);

	int getMileage();
	void setMileage(int);
	void addMileage(int);
	void subtractMileage(int);

	int getBookCount();
	void increaseBookCount();
	void decreaseBookCount();

};

