#include "QInt.h"

int main() {
	QInt x;
	scanQInt(x);
	printBin(x);

	x = rol(x, 129);
	printBin(x);

	return 0;
}