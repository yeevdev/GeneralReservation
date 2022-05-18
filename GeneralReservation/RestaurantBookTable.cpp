#include "RestaurantBookTable.h"

RestaurantBookTable::RestaurantBookTable(int tableNum, int size) {
	this->tableNum = tableNum;
	this->size = size;
	this->customerID = "";
	this->reserved = false;
	this->eating = false;
	this->reservedCount = 0;
}

int RestaurantBookTable::getTableNum() {
	return this->tableNum;
}

int RestaurantBookTable::getSize() {
	return this->size;
}

bool RestaurantBookTable::isReserved() {
	return this->reserved;
}

bool RestaurantBookTable::isEating() {
	return this->eating;
}

string RestaurantBookTable::getCustomerID() {
	return this->customerID;
}

int RestaurantBookTable::getReservedCount() {
	return this->reservedCount;
}

void RestaurantBookTable::reserve(string id) {
	this->customerID = id;
	this->reserved = true;
	this->reservedCount++;
}

void RestaurantBookTable::cancel() {
	this->customerID = "";
	this->reserved = false;
	this->reservedCount--;
}

void RestaurantBookTable::eat() {
	this->eating = true;
}

void RestaurantBookTable::complete() {
	this->eating = false;
}
