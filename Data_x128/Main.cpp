#include "TestMode.h"
#include "Console.h"

int main(int argc, char **argv) {
	if (argc == 1) {
		consoleMode();
	}
	else if (argc == 4) {
		TestMode(argv[1], argv[2], stoi(argv[3]));
	}
  
	system("pause");
	return 0;
}
