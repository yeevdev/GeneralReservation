#pragma once
#include "AirlineBookFlight.h"

AirlineBookFlight::AirlineBookFlight(string airport1, string airport2, string date, int time1, int time2) {
    this->departureAirport = airport1;
    this->arrivalAirport = airport2;
    this->date = date;
    this->departureTime = time1;
    this->arrivalTime = time2;

    seats.push_back(new AirlineBookSeat(BUSINESS));
    seats.push_back(new AirlineBookSeat(BUSINESS));
    seats.push_back(new AirlineBookSeat(ECONOMY));
    seats.push_back(new AirlineBookSeat(ECONOMY));
    seats.push_back(new AirlineBookSeat(ECONOMY));
    seats.push_back(new AirlineBookSeat(ECONOMY));
    seats.push_back(new AirlineBookSeat(BUSINESS));
    seats.push_back(new AirlineBookSeat(BUSINESS));
}

AirlineBookFlight::~AirlineBookFlight() {
    for (auto& seat : this->seats) {
        delete seat;
    }

    seats.clear();
}

string AirlineBookFlight::getDepartureAirport() {
    return this->departureAirport;
}

string AirlineBookFlight::getArrivalAirport() {
    return this->arrivalAirport;
}

string AirlineBookFlight::getDate() {
    return this->date;
}

int AirlineBookFlight::getDepartureTime() {
    return this->departureTime;
}

int AirlineBookFlight::getArrivalTime() {
    return this->arrivalTime;
}

AirlineBookSeat& AirlineBookFlight::getSeat(int seatNum) {
    return *this->seats[seatNum - 1];
}
