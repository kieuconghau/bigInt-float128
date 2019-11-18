#include "QInt.h"

int main() {
	QInt x, y;

	scanQInt(x);
	printBin(x);

	scanQInt(y);
	printBin(y);
	
	printBin(x * y);

	return 0;
}