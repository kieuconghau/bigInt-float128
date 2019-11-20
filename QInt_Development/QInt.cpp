#include "QInt.h"

/* Check if QInt is negative */
bool isNegative(QInt x) {
	return (x.data[0] >> 31) == 1;
}


/* Check if QInt is positive */
bool isPositive(QInt x) {
	return !isNegative(x) && !isZero(x);
}


/* Check if QInt is zero */
bool isZero(QInt x) {
	for (int i = 0; i < DATA_COUNT; ++i) {
		if (x.data[i] != 0)
			return false;
	}
	return true;
}

bool isOne(string str) {
	if (str[0] == '-')
		return false;

	for (int i = 0; i < str.size() - 1; ++i) {
		if (str[i] != '0')
			return false;
	}

	return str[str.size() - 1] == '1';
}

bool isZero(string str) {
	if (str[0] == '-')
		str[0] = '0';

	for (int i = 0; i < str.size(); ++i) {
		if (str[i] != '0')
			return false;
	}

	return true;
}

/* a. Scan QInt */
void scanQInt(QInt& x) {
	string str;
	cin >> str;

	bool* bit = new bool[BIT_SIZE]();
	bool is_not_overflow = decStrToBinStr(str, bit, BIT_SIZE);

	if (is_not_overflow)
		x = binToDec(bit);
	else
		cout << "\aError: Overflow" << endl;

	delete[] bit;
}


/* Convert decimal string to binary sequence */
bool decStrToBinStr(string str, bool* bit, int bit_size) {
	if (isZero(str)) {	// prevent case: str = "-0"
		for (int i = 0; i < bit_size; ++i)
			bit[i] = 0;

		return true;
	}

	bool is_negative = false;
	if (str[0] == '-') {
		is_negative = true;
		str[0] = '0';
	}

	while (bit_size > 1) {		// Ignore bit[0]: sign bit
		--bit_size;
		bit[bit_size] = posDecStrMod2(str);
		str = posDecStrDivide2(str);
	}

	if (is_negative) {
		int i = BIT_SIZE - 1;

		while (bit[i] == 0 && i >= 0) {
			--i;
		}

		if (i == -1) {		// 000...00 -> 100...00 (4 bits: -8)
			bit[0] = 1;
			return isOne(str);	// Check not overflow with the special case (4 bits: str = "-8")
		}

		--i;
		while (i >= 0) {
			bit[i] = !bit[i];
			--i;
		}
	}

	return isZero(str);		// Check not overflow
}


/* Positive decimal string divide 2 */
string posDecStrDivide2(string str) {	// Divisor = 2
	string quo;

	uint8_t re = 0;		// remainder
	uint8_t temp;

	for (int i = 0; i < str.size(); ++i) {
		temp = 10 * re + (str[i] - '0');
		quo += temp / 2 + '0';
		re = temp % 2;
	}
	
	return quo;
}


/* Positive decimal string mod 2 */
bool posDecStrMod2(string str) {		// Divisor = 2
	return (str[str.size() - 1] - '0') % 2 != 0;
}


/* b. Print QInt */
void printQInt(QInt x) {

}


/* Positive decimal string multiply 2 */
string posDecStrMultiply2(string str) {	// Factor = 2
	string prod(str.size() + 1, 0);



	return prod;
}


/* Positive decimal string add decimal string */
string posDecStrAddDecStr(string str1, string str2) {
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


/* e. Binary to Hexadecimal */
string binToHex(bool* bit) {
	string hex = "0x";

	for (int i = 0; i < BIT_SIZE; i += 4) {
		int dec = bit[i + 3] + bit[i + 2] * 2 + bit[i + 1] * 4 + bit[i] * 8;

		char ascii = (dec < 10) ? dec + 48 : dec - 10 + 65;
		string _ascii(&ascii);

		hex += _ascii[0];
	}

	return hex;
}


/* e. Hexdecimal to Binary */
string decToHex(QInt x) {
	bool* bit = decToBin(x);

	return binToHex(bit);
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

	if ((isPositive(x) && isPositive(y) && isNegative(sum)) ||
		(isNegative(x) && isNegative(y) && isPositive(sum))) {
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

	if ((isPositive(x) && isNegative(y) && isNegative(dif)) ||
		(isNegative(x) && isPositive(y) && isPositive(dif))) {
		cout << "\aWarning: overflow" << endl;
	}

	return dif;
}


/* g. * */
QInt operator*(QInt x, QInt y) {
	QInt Q = x;
	QInt M = y;
	QInt A;
	uint32_t q;
	uint32_t q_ = 0;

	for (int i = 0; i < BIT_SIZE; ++i) {
		q = Q.data[DATA_COUNT - 1] & 1;

		if (q == 0 && q_ == 1)
			A = A + M;
		else if (q == 1 && q_ == 0)
			A = A - M;
		
		q_ = q;

		Q = logicalShiftRight(Q, 1);
		Q.data[0] |= A.data[DATA_COUNT - 1] << 31;

		A = A >> 1;
	}

	return Q;
}


/* g. / */
QInt operator/(QInt x, QInt y) {
	if (isZero(x))		// return 0 if x == 0
		return x;
	if (isZero(y))		// warn if y == 0
		throw "Divisor cannot be zero!";

	bool is_negative = isNegative(x) ^ isNegative(y);		// sign of the result

	QInt one;			// 1
	one.data[DATA_COUNT - 1] = 1;
	
	if (isNegative(x))
		x = ~(x - one);		// covert the negative to the positive
	if (isNegative(y))
		y = ~(y - one);		// covert the negative to the positive

	
	QInt Q = x;		// Before: Dividend - After: Quotinent 
	QInt M = y;		// Divisor
	QInt A;			// Remainder

	for (int i = 0; i < BIT_SIZE; ++i) {
		// logicalShiftLeft A, Q
		A = A << 1;
		A.data[DATA_COUNT - 1] |= Q.data[0] >> (UINT_BIT_SIZE - 1);
		Q = Q << 1;

		A = A - M;

		if (isNegative(A)) {
			Q.data[DATA_COUNT - 1] &= ~1;		// ~1: 111..110
			A = A + M;
		}
		else {
			Q.data[DATA_COUNT - 1] |= 1;
		}
	}

	if (is_negative)
		Q = ~(Q - one);		// convert the positive (result) to the negative

	return Q;
}


/* h. == */
bool operator==(QInt x, QInt y) {
	for (int i = 0; i < DATA_COUNT; ++i) {
		if (x.data[i] != y.data[i])
			return false;
	}

	return true;
}


/* h. > */
bool operator>(QInt x, QInt y) {
	// Convert the range from [1000...000, 0111...111] to [0000...000, 1111...111] -> easier comparison
	x.data[0] += 1 << 31;
	y.data[0] += 1 << 31;

	// Compare (NOTE: now, x and y are not in 2's complement representation)
	uint32_t a;			// get the i_th bit of x from 0 to 127
	uint32_t b;			// get the i_th bit of y from 0 to 127
	for (int i = 0; i < BIT_SIZE; ++i) {
		a = (x.data[i / 32] >> (31 - i % 32)) & 1;
		b = (y.data[i / 32] >> (31 - i % 32)) & 1;

		if (a != b)
			return a > b;
	}

	return false;		// x == y
}


/* h. <= */
bool operator<=(QInt x, QInt y) {
	return !(x > y);
}


/* h. < */
bool operator<(QInt x, QInt y) {
	// Convert the range from [1000...000, 0111...111] to [0000...000, 1111...111] -> easier comparison
	x.data[0] += 1 << 31;
	y.data[0] += 1 << 31;

	// Compare (NOTE: now, x and y are not in 2's complement representation)
	uint32_t a;			// get the i_th bit of x from 0 to 127
	uint32_t b;			// get the i_th bit of y from 0 to 127
	for (int i = 0; i < BIT_SIZE; ++i) {
		a = (x.data[i / 32] >> (31 - i % 32)) & 1;
		b = (y.data[i / 32] >> (31 - i % 32)) & 1;

		if (a != b)
			return a < b;
	}

	return false;		// x == y
}


/* h. >= */
bool operator>=(QInt x, QInt y) {
	return !(x < y);
}


/* h. = */
QInt& QInt::operator=(QInt const & x) {
	for (int i = 0; i < DATA_COUNT; ++i) {
		this->data[i] = x.data[i];
	}
	
	return *this;
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


/* j. Shift left << (arithmetic) */
QInt operator<<(QInt x, int shift_bit_num) {
	return logicalShiftLeft(x, shift_bit_num);
}

/* Logical shift left */
QInt logicalShiftLeft(QInt x, int shift_bit_num) {
	while (shift_bit_num < 0)
		shift_bit_num += BIT_SIZE;

	shift_bit_num %= BIT_SIZE;
	
	if (shift_bit_num == 0)
		return x;

	int q = shift_bit_num / 32;
	int r = shift_bit_num % 32;
	int i = q;

	while (i < DATA_COUNT - 1) {
		if (r == 0)
			x.data[i - q] = x.data[i];
		else
			x.data[i - q] = (x.data[i] << r) | (x.data[i + 1] >> (32 - r));

		++i;
	}

	x.data[i - q] = x.data[i] << r;

	i = i - q + 1;
	while (i < DATA_COUNT) {
		x.data[i] = 0;
		++i;
	}

	return x;
}

/* j. Shift right >> (arithmetic) */
QInt operator>>(QInt x, int shift_bit_num) {
	bool is_negative = isNegative(x);

	x = logicalShiftRight(x, shift_bit_num);

	if (is_negative) {
		while (shift_bit_num < 0)
			shift_bit_num += BIT_SIZE;

		shift_bit_num %= BIT_SIZE;

		if (shift_bit_num == 0)
			return x;

		for (int j = 0; j < shift_bit_num; ++j) {
			x.data[j / 32] |= (1 << (31 - j % 32));
		}
	}

	return x;
}

/* Logical shift right */
QInt logicalShiftRight(QInt x, int shift_bit_num) {
	while (shift_bit_num < 0)
		shift_bit_num += BIT_SIZE;

	shift_bit_num %= BIT_SIZE;

	if (shift_bit_num == 0)
		return x;

	int q = shift_bit_num / 32;
	int r = shift_bit_num % 32;
	int i = DATA_COUNT - 1 - q;

	while (i > 0) {
		if (r == 0)
			x.data[i + q] = x.data[i];
		else
			x.data[i + q] = (x.data[i] >> r) | (x.data[i - 1] << (32 - r));

		--i;
	}

	x.data[i + q] = x.data[i] >> r;

	i = i + q - 1;
	while (i >= 0) {
		x.data[i] = 0;
		--i;
	}

	return x;
}


/* j. Rotate left */
QInt rol(QInt x, int rotate_bit_num) {
	QInt a = logicalShiftLeft(x, rotate_bit_num);
	QInt b = logicalShiftRight(x, BIT_SIZE - rotate_bit_num);

	return a | b;
}


/* j. Rotate right */
QInt ror(QInt x, int rotate_bit_num) {
	QInt a = logicalShiftRight(x, rotate_bit_num);
	QInt b = logicalShiftLeft(x, BIT_SIZE - rotate_bit_num);

	return a | b;
}

