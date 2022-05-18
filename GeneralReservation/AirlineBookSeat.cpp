#pragma once
#include "AirlineBookSeat.h"

AirlineBookSeat::AirlineBookSeat(SeatClass seatClass) {
	this->seatClass = seatClass;
	this->customerID = "";
	this->reserved = false;
}

void AirlineBookSeat::reserve(string id) {
	this->customerID = id;
	this->reserved = true;
}

void AirlineBookSeat::cancel() {
	this->customerID = "";
	reserved = false;
}

bool AirlineBookSeat::isReserved() {
	return this->reserved;
}

string AirlineBookSeat::getCustomerID() {
	return this->customerID;
}

SeatClass AirlineBookSeat::getSeatClass() {
	return this->seatClass;
}

int AirlineBookSeat::getPrice() {
	if (this->seatClass == ECONOMY) {
		return 50000;
	}
	else if (this->seatClass == BUSINESS) {
		return 100000;
	}
}
