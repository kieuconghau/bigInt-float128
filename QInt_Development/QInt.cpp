#include "QInt.h"

/* a. Scan QInt */
void scanQInt(QInt& x) {
	string str;
	cin >> str;

	bool is_negative = false;
	if (str[0] == '-') {
		is_negative = true;
		str[0] = '0';
	}

	bool* bit = new bool[BYTE * 8]();
	bool is_not_overflow = decStrToBinStr(str, bit, BYTE * 8);

	if (is_not_overflow) {
		/* Negative */
		if (is_negative) {
			int i = BYTE * 8 - 1;
			
			while (bit[i--] == 0);

			while (i >= 0) {
				bit[i] = !bit[i];
				--i;
			}
		}
		
		/* Turn on bit */
		x = binToDec(bit);
	}
	else {
		cout << "\aError: Overflow" << endl;
		throw;
	}

	delete[] bit;
}


/* Convert decimal string to binary sequence */
bool decStrToBinStr(string str, bool* bit, int bit_size)
{
	while (bit_size > 1) {		// Ignore bit[0]: sign bit
		--bit_size;
		bit[bit_size] = decStrMod2(str);
		str = decStrDivide2(str);
	}

	return stoi(str) == 0;		// Check not overflow
}


/* Decimal string divide 2 */
string decStrDivide2(string str) {	// Divisor = 2
	string quotient;

	/* Split str into many parts and store each part of them into 1 size_t */
	// 1. Count the number of parts
	int const part_count = (str.size() + PART_SIZE - 1) / PART_SIZE;

	// 2. Store each part which is split into 1 size_t
	size_t* part = new size_t[part_count];

	for (int i = 1; i < part_count; ++i) {
		part[part_count - i] = stoi(str.substr(str.size() - PART_SIZE * i, PART_SIZE));
	}
	part[0] = stoi(str.substr(0, str.size() - PART_SIZE * (part_count - 1)));


	/* Process */
	for (int i = 0; i < part_count - 1; ++i) {
		if (part[i] < 2 * (int)pow(10, PART_SIZE - 1))
			quotient += "0";

		quotient += to_string(part[i] / 2);
		part[i + 1] += (part[i] % 2) * (int)pow(10, PART_SIZE);
	}
	if (part[part_count - 1] < 2 * (int)pow(10, PART_SIZE - 1))
		quotient += "0";
	quotient += to_string(part[part_count - 1] / 2);


	/* Deallocate memory */
	delete[] part;

	return quotient;
}


/* Decimal string mod 2 */
bool decStrMod2(string str) {		// Divisor = 2
	return (str[str.size() - 1] - '0') % 2 != 0;
}


/* b. Print QInt */
void printQInt(QInt x) {

}


/* Decimal string multiple 2 */
string decStrMultiple2(string str) {	// Factor = 2
	string product(str.size() + 1, 0);



	return product;
}


/* Decimal string add decimal string */
string decStrAddDecStr(string str1, string str2) {
	string sum;



	return sum;
}


/* c. Decimal (QInt) to Binary sequence */
bool* decToBin(QInt x) {
	bool* bit = new bool[BYTE * 8]();



	return bit;
}


/* d. Binary sequence to Decimal (QInt) */
QInt binToDec(bool* bit) {
	QInt x;
	int k;

	for (int i = BYTE * 8 - 1; i >= 0; --i) {
		if (bit[i]) {
			k = i / 32;
			x.data[k] = x.data[k] | (1 << (31 - i % 32));
		}
	}

	return x;
}


/* j. Shift left << */
QInt& operator<<(QInt& x, size_t i) {


	return x;
}