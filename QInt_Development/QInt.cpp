#include "QInt.h"

bool isNegative(QInt x) {
	return (x.data[0] >> 31) == 1;
}

bool isPositive(QInt x) {
	return !isNegative(x) && !isZero(x);
}

bool isZero(QInt x) {
	for (int i = 0; i < DATA_COUNT; ++i) {
		if (x.data[i] != 0)
			return false;
	}
	return true;
}


/* a. Scan QInt */
void scanQInt(QInt& x) {
	string str;
	cin >> str;

	bool is_negative = false;
	if (str[0] == '-') {
		is_negative = true;
		str[0] = '0';
	}

	bool* bit = new bool[BIT_SIZE]();
	bool is_not_overflow = decStrToBinStr(str, bit, BIT_SIZE);

	if (is_not_overflow) {
		/* Negative */
		if (is_negative) {
			int i = BIT_SIZE - 1;
			
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
string decStrMultiply2(string str) {	// Factor = 2
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
	bool* bit = new bool[BIT_SIZE]();

	for (int i = BIT_SIZE - 1; i >= 0; --i) {
		bit[i] = (x.data[i / 32] >> (31 - i % 32)) & 1;
	}

	return bit;
}


/* Print QInt as a Binary sequence */
void printBin(QInt x) {
	bool* bit = decToBin(x);

	for (int i = 0; i < BIT_SIZE; ++i) {
		cout << bit[i];
		
		if (i % 8 == 7)
			cout << " ";
		if (i % 32 == 31)
			cout << endl;
	}

	delete[] bit;
}


/* d. Binary sequence to Decimal (QInt) */
QInt binToDec(bool* bit) {
	QInt x;
	int k;

	for (int i = BIT_SIZE - 1; i >= 0; --i) {
		if (bit[i]) {
			k = i / 32;
			x.data[k] = x.data[k] | (1 << (31 - i % 32));
		}
	}

	return x;
}


/* g. + */
QInt operator+(QInt x, QInt y) {
	QInt sum;
	uint32_t a;				// get the i_th bit of x from 127 to 0
	uint32_t b;				// get the i_th bit of y from 127 to 0
	uint32_t r = 0;			// remainder

	for (int i = BIT_SIZE - 1; i >= 0; --i) {
		a = (x.data[i / 32] >> (31 - i % 32)) & 1;
		b = (y.data[i / 32] >> (31 - i % 32)) & 1;
		
		sum.data[i / 32] |= (a ^ b ^ r) << (31 - i % 32);
		
		r = (a + b + r) >> 1;
	}

	if (r == 1) {
		cout << "\aWarning: overflow" << endl;
	}

	return sum;
}


/* g. - */
QInt operator-(QInt x, QInt y) {
	QInt dif;
	uint32_t a;				// get the i_th bit of x from 127 to 0
	uint32_t b;				// get the i_th bit of y from 127 to 0
	uint32_t d = 0;			// debt

	for (int i = BIT_SIZE - 1; i >= 0; --i) {
		a = (x.data[i / 32] >> (31 - i % 32)) & 1;
		b = (y.data[i / 32] >> (31 - i % 32)) & 1;

		dif.data[i / 32] |= (a ^ b ^ d) << (31 - i % 32);

		a += 2;				// borrow
		d = (a >> 1) - ((a - b - d) >> 1);
	}

	if (d == 1) {
		cout << "\aWarning: overflow" << endl;
	}

	return dif;
}


/* h. == */
bool operator==(QInt x, QInt y) {
	for (int i = 0; i < DATA_COUNT; ++i) {
		if (x.data[i] != y.data[i])
			return false;
	}
	return true;
}



/* i. AND */
QInt operator&(QInt x, QInt y) {
	for (int i = 0; i < DATA_COUNT; ++i) {
		x.data[i] &= y.data[i];
	}

	return x;
}


/* i. OR */
QInt operator|(QInt x, QInt y) {
	for (int i = 0; i < DATA_COUNT; ++i) {
		x.data[i] |= y.data[i];
	}

	return x;
}


/* i. XOR */
QInt operator^(QInt x, QInt y) {
	for (int i = 0; i < DATA_COUNT; ++i) {
		x.data[i] ^= y.data[i];
	}

	return x;
}


/* i. NOT */
QInt operator~(QInt x) {
	for (int i = 0; i < DATA_COUNT; ++i) {
		x.data[i] = ~x.data[i];
	}

	return x;
}


/* j. Shift left << */
QInt operator<<(QInt x, size_t shift_bit_num) {
	if (shift_bit_num < BIT_SIZE) {
		int q = shift_bit_num / 32;
		int r = shift_bit_num % 32;
		int i = q;

		while (i < DATA_COUNT - 1) {
			x.data[i - q] = (x.data[i] << r) | (x.data[i + 1] >> (32 - r));
			++i;
		}

		x.data[i - q] = x.data[i] << r;

		i = i - q + 1;
		while (i < DATA_COUNT) {
			x.data[i] = 0;
			++i;
		}
	}
	else {
		for (int i = 0; i < DATA_COUNT; ++i)
			x.data[i] = 0;
	}

	return x;
}


/* j. Shift right */
QInt operator>>(QInt x, size_t shift_bit_num) {
	bool is_negative = isNegative(x);

	if (shift_bit_num < BIT_SIZE) {
		int q = shift_bit_num / 32;
		int r = shift_bit_num % 32;
		int i = DATA_COUNT - 1 - q;

		while (i > 0) {
			x.data[i + q] = (x.data[i] >> r) | (x.data[i - 1] << (32 - r));
			--i;
		}

		x.data[i + q] = x.data[i] >> r;

		if (is_negative) {
			for (int j = 0; j < shift_bit_num; ++j) {
				x.data[j / 32] |= (1 << (31 - j % 32));
			}
		}
		else {
			i = i + q - 1;
			while (i >= 0) {
				x.data[i] = 0;
				--i;
			}
		}
	}
	else {
		if (is_negative) {
			for (int j = 0; j < BIT_SIZE; ++j) {
				x.data[j / 32] |= (1 << (31 - j % 32));
			}
		}
		else {
			for (int i = 0; i < DATA_COUNT; ++i)
				x.data[i] = 0;
		}
	}

	return x;
}


/* j. Rotate left */
QInt rol(QInt x, size_t rotate_bit_num) {
	rotate_bit_num %= BIT_SIZE;



	return x;
}


/* j. Rotate right */
QInt ror(QInt x, size_t rotate_bit_num) {
	rotate_bit_num %= BIT_SIZE;



	return x;
}