#include "QInt.h"
#include "Qfloat.h"

int main() {
	float y = 0;
	Qfloat x;
	scanQfloat(x);
	printBinaryQfloat(x);
	cout << endl;
	printQfloat(x);
	getchar();
	getchar();
	return 0;
}