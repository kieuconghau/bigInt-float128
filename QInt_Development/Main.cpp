#include "QInt.h"

int main() {
	QInt x;
	scanQInt(x);

	printBin(x);
	printBin(~x);
	x = ~x;
	printBin(x);
	x = ~~x;
	printBin(x);

	return 0;
}