#include "QInt.h"

int main() {
	QInt x, y;
	scanQInt(x);
	scanQInt(y);

	printBin(x);
	cout << endl;
	printBin(y);
	cout << endl;
	printBin(x & y);

	return 0;
}