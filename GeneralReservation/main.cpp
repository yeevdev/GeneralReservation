#include "Console.h"
#include "AirlineBook.h"


int main() {
	Console::printStartMsg();

	//프로그램 동적할당.
	AirlineBook& airlineBookProgram = *(new AirlineBook());

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
		}
		else if (selectedProgram == 3) {
			// 독서실 예약
			Console::clear();
		}
		else if (selectedProgram == 4) {
			Console::printExitMsg();
			break;
		}
	}

	return 0;
}