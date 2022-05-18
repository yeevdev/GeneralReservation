#pragma once

#include <iostream>
#include <string>
#include "Windows.h"


using namespace std;

class Console {
public:
	static void printENDL();
	static void clear();
	static int getInt();
	static string getString();
	static bool getYesOrNo();
	static string getFormattedInt(int);
	static void printStartMsg();
	static void printExitMsg();
	static int selectProgram();

	// ·Î±×ÀÎ
	static string getID();
	static string getPASSWORD();
	static string getName();
	static bool selectLoginSignUp();
	static void printLoginStartMsg();
	static void printLoginCompleteMsg(string);
	static void printLoginSignUpMsg();
	static void printLoginSignUpCompleteMsg();
	static void printLoginAlreadyIDExistMsg();
	static void printLoginFailMsg();

};

