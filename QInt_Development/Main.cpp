#include "QInt.h"

int main() {
	QInt x;
	
	scanQInt(x);
	printBin(x);

	printBin(x << 1 << 1);

	return 0;
}