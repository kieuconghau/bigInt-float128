/*

	Hi! I'm Buu. If there's any bug, that's because Buu is sleepy. Don't mind xD

*/

#include "Qfloat.h"

int multiply2(int *a, int n) {
	int r = 0;

	for (int i = n - 1; i >= 0; i--) {
		a[i] *= 2;
		a[i] += r;
		r = a[i] / pow(10, DIGITS);
		if (r == 1) a[i] -= pow(10, DIGITS);
	}

	return r;
}

int mod2(int *a, int n) {
	int result = a[n - 1] % 2;
	a[n - 1] /= 2;

	for (int i = n - 2; i >= 0; i--) {
		int r = a[i] % 2;
		a[i] = a[i] / 2;
		a[i + 1] += r * pow(10, DIGITS) / 2;
	}

	return result;
}

bool isZero(int *a, int n) {
	for (int i = n - 1; i >= 0; i--) {
		if (a[i] != 0) return false;
	}
	return true;
}

void processIntergralPart(string intergral, int nInt, int *_int, vector <bool> &binInt) {
	string d;

	for (int i = nInt - 1; i >= 1; i--) { // backward
		d = intergral.substr(intergral.size() - (nInt - i) * DIGITS, DIGITS); // split 8 digits
		_int[i] = stoi(d);
	}
	d = intergral.substr(0, intergral.size() - (nInt - 1) * DIGITS);
	_int[0] = stoi(d);

	while (!isZero(_int, nInt)) {
		binInt.insert(binInt.begin(), mod2(_int, nInt));
	}
}

bool processFractionalPart(string fractional, int nFrac, int *_frac, vector <bool> &binFrac, vector <bool> binInt) {
	string d;

	if (nFrac > 1) {
		for (int i = 0; i < nFrac - 1; i++) {
			d = fractional.substr(i*DIGITS, DIGITS);
			_frac[i] = stoi(d);
		}
		d = fractional.substr((nFrac - 1)*DIGITS, fractional.size() - (nFrac - 1)*DIGITS);
		while (d.size() < 8) d += '0'; // fill in d to get 8 digits
		_frac[nFrac - 1] = stoi(d);
	}
	else {
		while (fractional.size() < 8) fractional += '0';
		_frac[0] = stoi(fractional);
	}

	
	while (((BITS - (binInt.size() - 1) - binFrac.size()) > 0) && !isZero(_frac, nFrac)) {
		binFrac.insert(binFrac.end(),multiply2(_frac, nFrac));
	}

	return (binFrac.size() == 0);
}

void scanQfloat(Qfloat &x) {
	string str;
	cout << "x = "; cin >> str;

	// ==== PROCESS SIGN ====
	bool sign = (str[0] == '-'); //
	if (sign) str = str.substr(1, str.size() - 1);
	x.data[0] = x.data[0] | (sign << 31);


	// ==== SPLIT PART ====
	int idx_dot = 0; // index of "."
	while (idx_dot < str.size() && str[idx_dot] != '.') idx_dot++;  // find index of "."
	if (idx_dot == str.size())str += ".0";
	string intergral = str.substr(0, idx_dot); // intergral part of str
	string fractional = str.substr(idx_dot + 1, str.size() - idx_dot); // fractional part of str

	// ==== PROCESS INTERGRAL PART ====
	int nInt = (int)((intergral.size() % DIGITS == 0) ? (intergral.size() / DIGITS) : (intergral.size() / DIGITS) + 1); // calc range
	int *_int = new int[nInt]; // discrete intergral part
	vector <bool> binInt;
	processIntergralPart(intergral, nInt, _int, binInt);
	
	// ==== PROCESS FRACTIONAL PART ====
	int nFrac = (int)((fractional.size() % DIGITS == 0) ? (fractional.size() / DIGITS) : (fractional.size() / DIGITS) + 1); // calc range
	int *_frac = new int[nFrac]; // discrete intergral part
	vector <bool> binFrac;
	processFractionalPart(fractional, nFrac, _frac, binFrac, binInt);

	// ==== PROCESS EXPONENT ====
	int floating = 0;
	int exponent = 0;
	if (intergral == "0") { // check if 0.xxxx
		for (int i = 0; !binFrac[i]; i++) floating--;  // dot move to right
		floating--;
	}
	else floating = binInt.size() - 1; // dot move to left
	exponent = floating + (pow(2, 15 - 1) - 1);

	for (int i = 15; i >= 1 && exponent != 0; i--) {
		if (mod2(&exponent, 1)) {
			x.data[0] = x.data[0] | (1 << (31-i));
		}
	}

	// ==== LAST PROCESS ====
	int bit = 16;
	for (int i = 1; i < binInt.size(); i++) {
		int idx = (int)(bit / 32); // index of x.data[]
		x.data[idx] = x.data[idx] | (binInt[i] << (31 - (bit - 32 * idx)));
		bit++;
	}

	int start = 0;
	if (intergral == "0") start = - floating;
	for (int i = start; (bit <= BITS) && (i < binFrac.size()) ; i++) {
		int idx = (int)(bit / 32); // index of x.data[]
		x.data[idx] = x.data[idx] | (binFrac[i] << (31 - (bit - 32 * idx)));
		bit++;
	}

	// ==== DELOCATE ====
	delete _int;
	delete _frac;
}

void printBinaryQfloat(Qfloat x) {
	for (int i = 0; i < 128; i++) {
		int idx = (int)(i / 32);
		int bit = (x.data[idx] >> (31 -(i % 32))) & 1;
		cout << bit;
		if (i % 4 == 3) cout << "\t";
		if (i % 16 == 15) cout << "\n";
	}
}

Qfloat binToDec(bool *bit) {
	Qfloat x;

	for (int i = 0; i < BITS; i++) {
		int idx = (int)(i / 32);
		x.data[idx] = x.data[idx] | (bit[i] << (31 - (i - 32 * idx)));
	}
	return x;
}

bool *decToBin(Qfloat x) {
	bool *bit = new bool [BITS];

	for (int i = 0; i < BITS; i++) {
		int idx = (int)(i / 32);
		bit[i] = (x.data[idx] >> (31 - (i % 32))) & 1;
	}
	return bit;
}