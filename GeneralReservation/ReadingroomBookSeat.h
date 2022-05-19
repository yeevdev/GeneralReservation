#pragma once
#include "Console.h"
class ReadingroomBookSeat {
public:
	ReadingroomBookSeat();

private:
	//string customerID;
	string reservedTime[14];

public:
	void reserve(string, int, int);
	void cancel(string);

	bool isReserved(int);
	string getCustomerID(int);
};
