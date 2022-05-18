#pragma once

#include "Console.h"
#include <vector>
#include "AirlineBookConsole.h"
#include "AirlineBookUser.h"
#include "AirlineBookFlight.h";
#include "AirlineBookTicket.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_YELLOW "\x1b[33m"


class AirlineBookConsole : public Console {
public:
	static void printWelcomeMsg();
	static void printExitMsg();
	static void printUserData(AirlineBookUser&);
	static void printSameAirportMsg();
	static void printFlight(AirlineBookFlight&, int);
	static void printSeats(AirlineBookFlight&, string);
	static void printNotEnoughMoney();
	static void printReserveCompleteMsg();
	static void printRoundTicketMsg();
	static void printNotExistTicket();
	static void printStatBookCount(AirlineBookUser&);
	static void printStatSeatCount(vector<AirlineBookTicket*>&);
	static int selectMenu();
	static int selectFlight(vector<AirlineBookFlight*>&);
	static int selectSeat(AirlineBookFlight&, int);
	static int selectCancelTicket(vector<AirlineBookTicket*>&);
	static int selectShowTicket(vector<AirlineBookTicket*>&);
	static string selectDate(vector<string>&);
	static string selectDepartureAirport();
	static string selectArrivalAirport();
	static bool selectRoundTicket();
};

