#include "TestMode.h"

int main(int argc, char **argv) {
	if (argc == 1) {
		// Console mode here
	}
	else if (argc == 4) {
		TestMode(argv[1], argv[2], stoi(argv[3]));
	}

	return 0;
}
