#include "RestaurantBookReservation.h"

RestaurantBookReservation::RestaurantBookReservation(string id, RestaurantBookTable* pTable, int num) {
	this->customerID = id;
	this->customerNum = num;
	this->pTable = pTable;
}

string RestaurantBookReservation::getCustomerID() {
	return this->customerID;
}

RestaurantBookTable& RestaurantBookReservation::getTable() {
	return *this->pTable;
}

int RestaurantBookReservation::getCustomerNum() {
	return this->customerNum;
}
