#pragma once
#include "AirlineBookFlight.h"


class AirlineBookTicket {
public:
	AirlineBookTicket(string, AirlineBookFlight*, int);

private:
	string customerID;
	AirlineBookFlight* pThisFlight;
	int seatNum;

public:
	string getCustomerID();
	AirlineBookFlight& getFlight();
	int getSeatNum();
};

