#include "QInt.h"

int main() {
	QInt x;
	
	scanQInt(x);
	for (int i = 0; i < 4; ++i) {
		cout << x.data[i] << endl;
	}

	return 0;
}