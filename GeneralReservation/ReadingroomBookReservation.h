#pragma once
#include "Console.h"
#include "ReadingroomBookSeat.h"
class ReadingroomBookReservation {
public:
	ReadingroomBookReservation(string, ReadingroomBookSeat*, int, int);

private:
	string id;
	int start;
	int end;
	ReadingroomBookSeat* seat;

public:
	string getID();
	ReadingroomBookSeat& getSeat();
	int getStartTime();
	int getEndTime();

};

