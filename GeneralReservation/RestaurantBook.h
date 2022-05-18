#pragma once
#include "UserManager.h"
#include "Console.h"
#include <vector>
#include "RestaurantBookTable.h"
#include "RestaurantBookReservation.h"

class RestaurantBook {
public:
	RestaurantBook();
	~RestaurantBook();

private:
	UserManager manager;
	
	vector<RestaurantBookTable*> tables;
	vector<RestaurantBookReservation*> reservations;
	vector<string> waitings;

public:
	void run();

	void reserve(string);
	void cancel(string);
	void wait(string);
	void show(string);
	void completeEating(string);
	void stat();
};

