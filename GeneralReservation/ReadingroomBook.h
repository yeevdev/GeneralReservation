#pragma once
#include "UserManager.h"
#include "ReadingroomBookSeat.h"
#include "ReadingroomBookReservation.h"
#include <vector>
class ReadingroomBook {
public:
	ReadingroomBook();
	//~ReadingroomBook();

private:
	int maleCount;
	int femaleCount;
	UserManager manager;

	vector<vector<ReadingroomBookSeat*>> seats;
	vector<ReadingroomBookReservation*> reservations;

public:
	void run();

	void reserve(string);
	void cancel(string);
	void show(string);
	void stat();
};

