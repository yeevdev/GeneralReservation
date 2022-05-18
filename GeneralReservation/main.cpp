#include "Console.h"


int main() {
	Console::printStartMsg();

	//프로그램 동적할당.

	while (true) {
		int selectedProgram = Console::selectProgram();

		if (selectedProgram == 1) {
			// 항공권 예약
			Console::clear();

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