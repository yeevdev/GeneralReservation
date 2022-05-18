#pragma once

#include <string>

using namespace std;

enum SeatClass {
	ECONOMY, BUSINESS
};

class AirlineBookSeat {
public:
	AirlineBookSeat(SeatClass);

private:
	SeatClass seatClass;
	string customerID;
	bool reserved;

public:
	void reserve(string);
	void cancel();

	bool isReserved();
	string getCustomerID();
	SeatClass getSeatClass();
	int getPrice();

};


