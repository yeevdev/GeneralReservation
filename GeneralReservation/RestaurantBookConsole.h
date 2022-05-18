#pragma once
#include "Console.h"
#include "RestaurantBookTable.h"
#include <vector>
#include "RestaurantBookReservation.h"

class RestaurantBookConsole : public Console {
public:
	static int getAge();
	static int getPeopleNum();
	static void printTooYoungAge();
	static void printWelcomeMsg();
	static void printExitMsg();
	static void printReserveCompleteMsg();
	static void printTables(vector<RestaurantBookTable*>&, int);
	static void printNotExistReservationMsg();
	static void printCancelCompleteMsg();
	static void printShowReservation(RestaurantBookReservation&);
	static void printIsEatingMsg();
	static void printNotExistWaitingMsg();
	static void printWaitingMsg(vector<string>&);
	static void printNowWaitingMsg(vector<string>&, int);
	static void printNotEating();
	static void printStat();
	static void printStatTable(int, int);
	static int selectMenu();
	static int selectTable(vector<RestaurantBookTable*>&, int);
};

