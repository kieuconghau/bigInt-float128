#include "QInt.h"

int main() {
	QInt x;
	
	scanQInt(x);
	printBin(x);

	printBin(x << 100);

	return 0;
}