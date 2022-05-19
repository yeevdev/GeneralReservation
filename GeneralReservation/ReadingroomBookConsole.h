#pragma once
#include "Console.h"
#include "ReadingroomBookSeat.h"
#include "ReadingroomBookReservation.h"
#include "UserManager.h"
#include <vector>
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

class ReadingroomBookConsole : public Console {
public:
	static int getAge();
	static int getStartTime();
	static int getEndTime();
	static int getRow();
	static int getCulumn();
	static string getGender();
	static void printLoginStartMsg();
	static void printWelcomeMsg();
	static void printExitMsg();
	static void printReserveMsg();
	static void printSeats(UserManager&, vector<vector<ReadingroomBookSeat*>>&, string, int, int);
	static void printReserveCompleteMsg();
	static void printReserveFailMsg();
	static void printNotExistReservationMsg();
	static void printCancelCompleteMsg();
	static void showSeats(vector<ReadingroomBookReservation*>&, string);
	static void showStat(int, int);
	static int selectMenu();
};

