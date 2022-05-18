#include "Console.h"
#include "AirlineBook.h"


int main() {
	Console::printStartMsg();

	//���α׷� �����Ҵ�.
	AirlineBook& airlineBookProgram = *(new AirlineBook());

	while (true) {
		int selectedProgram = Console::selectProgram();

		if (selectedProgram == 1) {
			// �װ��� ����
			Console::clear();
			airlineBookProgram.run();

		}
		else if (selectedProgram == 2) {
			// �Ĵ� ����
			Console::clear();
		}
		else if (selectedProgram == 3) {
			// ������ ����
			Console::clear();
		}
		else if (selectedProgram == 4) {
			Console::printExitMsg();
			break;
		}
	}

	return 0;
}