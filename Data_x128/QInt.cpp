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


/* Check if QInt is the minimum QInt: 100...000 */
bool isMinQInt(QInt x) {
	for (int i = 1; i < DATA_COUNT; ++i) {
		if (x.data[i] != 0)
			return false;
	}

	return x.data[0] == 1 << 31;
}


/* Check if a string is one */
bool isOne(string str) {
	if (str[0] == '-')
		return false;

	for (int i = 0; i < str.size() - 1; ++i) {
		if (str[i] != '0')
			return false;
	}

	return str[str.size() - 1] == '1';
}


/* Check if a string is zero*/
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

	// Convert a decimal string to a binary sequence (string -> bool*) and check overflow
	bool* bit = new bool[BIT_COUNT]();
	bool is_not_overflow = decStrToBinStr(str, bit, BIT_COUNT);

	if (is_not_overflow)
		x = binToDecQInt(bit);			// Convert a binary sequence to QInt (bool* -> QInt)
	else
		cout << "\aError: Overflow" << endl;

	delete[] bit;
}


/* Convert a decimal string to a binary sequence */
bool decStrToBinStr(string str, bool* bit, int bit_count) {
	if (isZero(str)) {		// Case: str = "-0"
		for (int i = 0; i < bit_count; ++i)
			bit[i] = 0;

		return true;
	}
	
	// Check negative, if this decimal string is negative, convert it to a positive form (string -> string)
	bool is_negative = false;
	if (str[0] == '-') {
		is_negative = true;
		str[0] = '0';
	}

	// Convert a positive decimal string to a binary sequence (string -> bool*)
	while (bit_count > 1) {						// Ignore bit[0]: sign bit
		--bit_count;
		bit[bit_count] = posDecStrMod2(str);	// Modulo 2
		str = posDecStrDivideBy2(str);			// Divide 2
	}

	// If this number is negative, convert the positive form to the negative form (bool* -> bool*)
	if (is_negative) {
		int i = BIT_COUNT - 1;

		// Find the index of the-first-bit-1 from right to left
		while (bit[i] == 0 && i >= 0) {
			--i;
		}

		// If there is no bit-1 in this sequence
		if (i == -1) {
			bit[0] = 1;			// Convert: 000...00 -> 100...00 (4 bits: -8)
			
			return isOne(str);	// Check not overflow with the special case (4 bits: str = "-8")
		}

		// If bit-1 is dectected in this sequence, revert each bit (0 -> 1, 1 -> 0) from i to 0
		--i;
		while (i >= 0) {
			bit[i] = !bit[i];
			--i;
		}
	}

	return isZero(str);		// Check not overflow
}


/* Positive decimal string divide 2 */
string posDecStrDivideBy2(string str) {	// Divisor = 2
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
	string str_data[DATA_COUNT];		// 4 int's in QInt struct expressed in string form.
	string output;			// Output string

	if (isNegative(x)) {
		output += "-";

		// Convert QInt from the negative form to the positve form
		QInt one;
		one.data[DATA_COUNT - 1] |= 1;

		if (!isMinQInt(x))		// If x is MIN_QINT, we don't need to convert it to th positive form.
			x = ~(x - one);
	}

	// Convert 'data' in QInt to string form
	for (int i = 0; i < DATA_COUNT; i++) {
		str_data[i] = to_string(x.data[i]);
	}

	// Multiply str_data[2] by 2^32, str_data[1] by 2^64,
	// and str_data[0] by 2^96
	for (int i = 1; i < DATA_COUNT; i++) {
		if (x.data[DATA_COUNT - 1 - i] > 0) {
			for (int j = 0; j < 32 * i; j++) {
				str_data[DATA_COUNT - 1 - i] = posDecStrMultiplyBy2(str_data[DATA_COUNT - 1 - i]);
			}
		}
	}

	for (int i = 1; i < DATA_COUNT; i++) {
		str_data[0] = posDecStrAddPosDecStr(str_data[0], str_data[i]);
	}

	output += str_data[0];

	cout << output << endl;
}


/* Positive decimal string multiply 2 */
string posDecStrMultiplyBy2(string str) {	// Factor = 2
	string prod;

	uint8_t carry = 0;	// The number which will be "carried" to the preceding digit
	uint8_t temp;

	for (int i = str.size() - 1; i >= 0; i--) {
		temp = 2 * (str[i] - '0') + carry;
		prod.insert(0, 1, (temp % 10) + '0');
		carry = temp / 10;
	}

	if (carry) {
		prod.insert(0, 1, '1');
	}

	return prod;
}


/* Positive decimal string add decimal string */
string posDecStrAddPosDecStr(string str1, string str2) {
	string sum;

	uint8_t carry = 0;
	uint8_t temp;
	int i1 = str1.size() - 1, i2 = str2.size() - 1;

	while (i1 >= 0 && i2 >= 0) {
		temp = (str1[i1--] - '0') + (str2[i2--] - '0') + carry;
		sum.insert(0, 1, (temp % 10) + '0');
		carry = temp / 10;
	}

	while (i1 >= 0) {
		temp = (str1[i1--] - '0') + carry;
		sum.insert(0, 1, (temp % 10) + '0');
		carry = temp / 10;
	}

	while (i2 >= 0) {
		temp = (str2[i2--] - '0') + carry;
		sum.insert(0, 1, (temp % 10) + '0');
		carry = temp / 10;
	}

	if (carry) {
		sum.insert(0, 1, '1');
	}

	return sum;
}


/* c. Decimal (QInt) to Binary sequence */
bool* decToBin(QInt x) {
	bool* bit = new bool[BIT_COUNT]();

	for (int i = BIT_COUNT - 1; i >= 0; --i) {
		bit[i] = (x.data[i / 32] >> (31 - i % 32)) & 1;
	}

	return bit;
}


/* Print QInt as a Binary sequence */
void printBin(QInt x) {
	bool* bit = decToBin(x);

	for (int i = 0; i < BIT_COUNT; ++i) {
		cout << bit[i];
		
		if (i % 8 == 7)
			cout << " ";
		if (i % 32 == 31)
			cout << endl;
	}

	delete[] bit;
}


/* d. Binary sequence to Decimal (QInt) */
QInt binToDecQInt(bool* bit) {
	QInt x;

	for (int i = BIT_COUNT - 1; i >= 0; --i) {
		if (bit[i]) {
			x.data[i / 32] |= (1 << (31 - i % 32));
		}
	}

	return x;
}


/* e. Binary to Hexadecimal */
string binToHex(bool* bit) {
	string hex = "0x";

	for (int i = 0; i < BIT_COUNT; i += 4) {
		int dec = bit[i + 3] + bit[i + 2] * 2 + bit[i + 1] * 4 + bit[i] * 8;

		char ascii = (dec < 10) ? dec + '0' : dec - 10 + 'A';
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
	uint8_t a;				// get the i_th bit of x from 127 to 0
	uint8_t b;				// get the i_th bit of y from 127 to 0
	uint8_t r = 0;			// remainder

	for (int i = BIT_COUNT - 1; i >= 0; --i) {
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
	uint8_t a;				// get the i_th bit of x from 127 to 0
	uint8_t b;				// get the i_th bit of y from 127 to 0
	uint8_t d = 0;			// debt

	for (int i = BIT_COUNT - 1; i >= 0; --i) {
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

	for (int i = 0; i < BIT_COUNT; ++i) {
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

	bool is_negative = isNegative(x) ^ isNegative(y);		// sign of the quotient

	QInt one;			// 1
	one.data[DATA_COUNT - 1] = 1;
	
	if (isNegative(x))
		x = ~(x - one);		// covert the negative to the positive
	if (isNegative(y))
		y = ~(y - one);		// covert the negative to the positive

	
	QInt Q = x;		// Before: Dividend - After: Quotinent 
	QInt M = y;		// Divisor
	QInt A;			// Remainder

	for (int i = 0; i < BIT_COUNT; ++i) {
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
	uint8_t a;			// get the i_th bit of x from 0 to 127
	uint8_t b;			// get the i_th bit of y from 0 to 127
	for (int i = 0; i < BIT_COUNT; ++i) {
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
	uint8_t a;			// get the i_th bit of x from 0 to 127
	uint8_t b;			// get the i_th bit of y from 0 to 127
	for (int i = 0; i < BIT_COUNT; ++i) {
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
	// Convert shift_bit_num to [0, BIT_COUNT - 1]
	while (shift_bit_num < 0)
		shift_bit_num += BIT_COUNT;
	shift_bit_num %= BIT_COUNT;
	
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
			shift_bit_num += BIT_COUNT;

		shift_bit_num %= BIT_COUNT;

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
		shift_bit_num += BIT_COUNT;

	shift_bit_num %= BIT_COUNT;

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
	QInt b = logicalShiftRight(x, BIT_COUNT - rotate_bit_num);

	return a | b;
}


/* j. Rotate right */
QInt ror(QInt x, int rotate_bit_num) {
	QInt a = logicalShiftRight(x, rotate_bit_num);
	QInt b = logicalShiftLeft(x, BIT_COUNT - rotate_bit_num);

	return a | b;
}

