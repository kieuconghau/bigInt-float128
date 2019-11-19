#include "QInt.h"
#include <bitset>
using namespace std;

int main() {
	QInt x, y;

	scanQInt(x);
	printBin(x);

	scanQInt(y);
	printBin(y);
	
	cout << endl;
	printBin(x + y);

	return 0;
}