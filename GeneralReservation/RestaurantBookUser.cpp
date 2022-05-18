#include "RestaurantBookUser.h"

RestaurantBookUser::RestaurantBookUser(string id, string password, string name, int age) : User(id, password, name) {
	this->age = age;
	this->eating = false;
}

int RestaurantBookUser::getAge() {
	return this->age;
}

bool RestaurantBookUser::isEating() {
	return this->eating;
}

void RestaurantBookUser::setEating(bool eating) {
	this->eating = eating;
}
