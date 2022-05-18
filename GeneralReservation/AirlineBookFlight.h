#pragma once

#include <vector>
#include "AirlineBookSeat.h"

using namespace std;

class AirlineBookFlight {
public:
	AirlineBookFlight(string, string, string, int, int);
	~AirlineBookFlight();

private:
	string departureAirport;
	string arrivalAirport;
	string date;
	int departureTime;
	int arrivalTime;

	vector<AirlineBookSeat*> seats;

public:
	string getDepartureAirport();
	string getArrivalAirport();
	string getDate();
	int getDepartureTime();
	int getArrivalTime();

	AirlineBookSeat& getSeat(int);
};

