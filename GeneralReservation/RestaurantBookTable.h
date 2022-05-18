#pragma once
#include "Console.h"

class RestaurantBookTable {
public:
	RestaurantBookTable(int, int);

private:
	int tableNum;
	int size;
	bool reserved;
	bool eating;
	string customerID;
	int reservedCount;

public:
	int getTableNum();
	int getSize();
	bool isReserved();
	bool isEating();
	string getCustomerID();
	int getReservedCount();

	void reserve(string);
	void cancel();
	
	void eat();
	void complete();

};

