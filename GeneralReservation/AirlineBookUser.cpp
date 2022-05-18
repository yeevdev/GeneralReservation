#pragma once
#include "AirlineBookUser.h"

AirlineBookUser::AirlineBookUser(string id, string password, string name) 
	: User(id, password, name) {
	setMoney(500000);
	setMileage(0);
	this->bookCount = 0;
}

int AirlineBookUser::getMoney() {
	return this->money;
}

void AirlineBookUser::setMoney(int money) {
	this->money = money;
}

void AirlineBookUser::addMoney(int money) {
	this->money += money;
}

void AirlineBookUser::subtractMoney(int money) {
	this->money -= money;
}

int AirlineBookUser::getMileage() {
	return this->mileage;
}

void AirlineBookUser::setMileage(int mile) {
	this->mileage = mile;
}

void AirlineBookUser::addMileage(int mile) {
	this->mileage += mile;
}

void AirlineBookUser::subtractMileage(int mile) {
	this->mileage -= mile;
}

int AirlineBookUser::getBookCount() {
	return this->bookCount;
}

void AirlineBookUser::increaseBookCount() {
	this->bookCount++;
}

void AirlineBookUser::decreaseBookCount() {
	this->bookCount--;
}
