#include "QInt.h"

int mod2(int *a, int n) {
	int result = a[n - 1] % 2;
	a[n - 1] /= 2;

	for (int i = n - 2; i >= 0; i--) {
		int r = a[i] % 2;
		a[i] /= 2;
		a[i + 1] += r * pow(10, 8 * (n - i - 1)) / 2;
	}

	return result;
}

bool isZero(int *a, int n) {
	for (int i = n - 1; i >= 0; i--) {
		if (a[i] != 0) return false;
	}
	return true;
}

void scanQInt(QInt &x) {
	string temp;
	cout << "x = "; cin >> temp;

	if (temp.size() > 39) { // check overflow
		cout << "Error: Overflow." << endl;
		return;
	}

	string d; // substring
	int n = (int)((temp.size() % 8 == 0) ? (temp.size() / 8) : (temp.size() / 8) + 1); // calc range
	int *input = new int[n]; // create array to split string

	for (int i = n - 1; i >= 1; i--) { // backward
		d = temp.substr(temp.size() - i * 8, 8); // split 8 digit
		input[i] = stoi(d);
	}
	d = temp.substr(0, temp.size() - (n - 1) * 8);
	input[0] = stoi(d);

	int bit = 127;
	while (!isZero(input, n)) {
		int idx = (int)(bit / 32); // index of x.data[]

		if (mod2(input, n)) {
			x.data[idx] = x.data[idx] | (1 << (bit - 32*idx));
		}

		bit--;
	}
}

void printBinaryQInt(QInt x) {
	for (int i = 0; i < 128; i++) {
		int idx = (int)(i / 32);
		int bit = (x.data[idx] >> (i % 32)) & 1;
		cout << bit;
		if (i % 16 == 15) cout << "\t";
	}
}