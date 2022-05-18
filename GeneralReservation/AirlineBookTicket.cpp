#pragma once
#include "AirlineBookTicket.h"

AirlineBookTicket::AirlineBookTicket(string id, AirlineBookFlight* pFlight, int seatNum) {
	this->customerID = id;
	this->pThisFlight = pFlight;
	this->seatNum = seatNum;
}

string AirlineBookTicket::getCustomerID() {
	return this->customerID;
}

AirlineBookFlight& AirlineBookTicket::getFlight() {
	return *this->pThisFlight;
}

int AirlineBookTicket::getSeatNum() {
	return this->seatNum;
}
