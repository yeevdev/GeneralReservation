#include "Console.h"


int main() {
	Console::printStartMsg();

	//���α׷� �����Ҵ�.

	while (true) {
		int selectedProgram = Console::selectProgram();

		if (selectedProgram == 1) {
			// �װ��� ����
			Console::clear();

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