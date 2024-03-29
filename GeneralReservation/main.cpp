#include "Console.h"
#include "AirlineBook.h"
#include "RestaurantBook.h"
#include "ReadingroomBook.h"


int main() {
	Console::printStartMsg();

	//프로그램 동적할당.
	AirlineBook& airlineBookProgram = *(new AirlineBook());
	RestaurantBook& restaurantBookProgram = *(new RestaurantBook());
	ReadingroomBook& readingroomBookProgram = *(new ReadingroomBook());

	while (true) {
		int selectedProgram = Console::selectProgram();

		if (selectedProgram == 1) {
			// 항공권 예약
			Console::clear();
			airlineBookProgram.run();

		}
		else if (selectedProgram == 2) {
			// 식당 예약
			Console::clear();
			restaurantBookProgram.run();
		}
		else if (selectedProgram == 3) {
			// 독서실 예약
			Console::clear();
			readingroomBookProgram.run();
		}
		else if (selectedProgram == 4) {
			Console::printExitMsg();
			break;
		}
	}

	return 0;
}