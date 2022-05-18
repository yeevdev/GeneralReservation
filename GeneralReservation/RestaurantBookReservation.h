#pragma once

#include "Console.h"
#include "RestaurantBookTable.h"
class RestaurantBookReservation {
public:
	RestaurantBookReservation(string, RestaurantBookTable*, int);

private:
	string customerID;
	RestaurantBookTable* pTable;
	int customerNum;

public:
	string getCustomerID();
	RestaurantBookTable& getTable();
	int getCustomerNum();
};

