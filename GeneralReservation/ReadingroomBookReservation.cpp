#include "ReadingroomBookReservation.h"

ReadingroomBookReservation::ReadingroomBookReservation(string id, ReadingroomBookSeat* pSeat, int start, int end) {
	this->id = id;
	this->seat = pSeat;
	this->start = start;
	this->end = end;
}

string ReadingroomBookReservation::getID() {
	return this->id;
}

ReadingroomBookSeat& ReadingroomBookReservation::getSeat() {
	return *seat;
}

int ReadingroomBookReservation::getStartTime() {
	return this->start;
}

int ReadingroomBookReservation::getEndTime() {
	return this->end;
}
