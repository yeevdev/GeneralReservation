#pragma once

#include <vector>
#include "AirlineBookConsole.h"
#include "AirlineBookFlight.h"
#include "AirlineBookLogin.h"
#include "AirlineBookSeat.h"
#include "AirlineBookTicket.h"
#include "AirlineBookUser.h"
using namespace std;


class AirlineBook {
public:
	AirlineBook();
	~AirlineBook();

private:
	UserManager manager;
	vector<AirlineBookFlight*> flights;
	vector<AirlineBookTicket*> tickets;

	vector<string> dates;
	vector<string> airports;

public:
	void run();

	void reserve(string);
	void show(string);
	void cancel(string);
	void stat(string);

};

