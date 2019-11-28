#include "TestMode.h"

/* Almost the same as scanQInt */
QInt DecStrToQInt(string dec_str) {
	QInt x;
	
	bool* bit = new bool[BIT_COUNT]();
	bool is_not_overflow = decStrToBinStr(dec_str, bit, BIT_COUNT);

	if (is_not_overflow)
		x = binToDecQInt(bit);

	delete[] bit;

	return x;
}

/* Almost the same as printQInt */
string QIntToDecStr(QInt x) {
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

	return output;
}

bool* BinStrToBoolArr(string bin_str) {
	bool* bit = new bool[BIT_COUNT]();
	
	int j = BIT_COUNT - 1;
	for (int i = bin_str.size() - 1; i >= 0; i--) {
		bit[j] = bin_str[i];
		j--;
	}

	return bit;
}

string QIntBoolArrToBinStr(bool* bit) {
	string bin_str;

	int i = 0;
	while (bit[i] == false) {
		i++;
	}

	while (i < BIT_COUNT) {
		bin_str += bit[i];
		i++;
	}

	return bin_str;
}

bool* HexToBin(string hex) {
	QInt x = hexToDec(hex);
	
	return decToBin(x);
}


/* Copied from scanQfloat */
Qfloat FloatStrToQFloat(string str) {
	Qfloat x;

	// ==== PROCESS SIGN ====
	bool sign = (str[0] == '-'); //
	if (sign) str = str.substr(1, str.size() - 1);
	x.data[0] = x.data[0] | (sign << 31);


	// ==== SPLIT PART ====
	int idx_dot = 0; // index of "."
	while (idx_dot < str.size() && str[idx_dot] != '.') idx_dot++;  // find index of "."
	if (idx_dot == str.size())str += ".0";
	string integral = str.substr(0, idx_dot); // integral part of str
	string fractional = str.substr(idx_dot + 1, str.size() - idx_dot); // fractional part of str

	// ==== PROCESS INTEGRAL PART ====
	int nInt = (int)((integral.size() % DIGITS == 0) ? (integral.size() / DIGITS) : (integral.size() / DIGITS) + 1); // calc range
	vector <int> _int(nInt);
	vector <bool> binInt;
	processIntegralPart(integral, _int, binInt);

	// ==== PROCESS FRACTIONAL PART ====
	int nFrac = (int)((fractional.size() % DIGITS == 0) ? (fractional.size() / DIGITS) : (fractional.size() / DIGITS) + 1); // calc range
	vector <int> _frac(nFrac);
	vector <bool> binFrac;
	processFractionalPart(fractional, _frac, binFrac, binInt);

	if (nFrac == 1 && nInt == 1 && binFrac.size() == 0 && binInt.size() == 0) return x; // Qfloat 0

	// ==== PROCESS EXPONENT ====
	int floating = 0;
	int exponent = 0;
	if (integral == "0") { // check if 0.xxxx
		floating = checkUnderflow(binFrac);
		if (!floating) { // check if Underflow
			cout << "Error: Underflow" << endl;
			return x;
		}
	}
	else floating = binInt.size() - 1; // dot move to left
	exponent = (floating > (-pow(2, EXPONENT - 1) + 2)) ? floating + (pow(2, EXPONENT - 1) - 1) : 0; /* Check exponent is normal or denormalized */

	if (exponent > (pow(2, 15) - 1)) {	// check if Overflow
		cout << "Error: Overflow" << endl;
		return x;
	}

	vector <int> ex;
	ex.push_back(exponent);

	for (int i = 15; i >= 1 && !isZero(ex); i--) {
		if (mod2(ex)) {
			x.data[0] = x.data[0] | (1 << (31 - i));
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
	if (integral == "0") {
		start = (floating > (-pow(2, EXPONENT - 1) + 2)) ? (-floating) : (-pow(2, EXPONENT - 1) + 2 - 1);
	}
	for (int i = start; (bit <= BITS) && (i < binFrac.size()); i++) {
		int idx = (int)(bit / 32); // index of x.data[]
		x.data[idx] = x.data[idx] | (binFrac[i] << (31 - (bit - 32 * idx)));
		bit++;
	}

	return x;
}

/* Copied from printQfloat */
string QFloatToFloatStr(Qfloat x) {
	int bit;
	discrete _x;

	// Calculate EXPONENT
	int exponent = 0;
	for (int i = 15; i >= 0; i--) {
		bit = (x.data[0] >> (31 - i)) & 1;
		exponent += bit * pow(2, 15 - i);
	}
	exponent -= (pow(2, EXPONENT - 1) - 1);

	// Initial
	if (exponent == -(pow(2, EXPONENT - 1) - 1)) { // Check if Qfloat is Denormalize
		_x._int.push_back(0); // Initial 0.xxxx
		exponent++;
	}
	else {
		_x._int.push_back(1); // Initial 1.xxxx
	}
	_x._frc.push_back(0); // 0.0 or 1.0
	discrete temp; // Initial 1.0
	temp._int.push_back(1);
	temp._frc.push_back(0);

	// Find index of the first bit 1
	int i = 16;
	bit = 0;
	while (!bit) {
		int idx = (int)(i / 32);
		bit = (x.data[idx] >> (31 - (i % 32))) & 1;
		i++;
	}

	// Prepare temp = 2^-(idx-16) 
	if (i <= BITS) {
		for (int j = 0; j < i - 16; j++) {
			discreteDivideBy2(temp);
		}
		_x = discreteSum(_x, temp);
	}

	// Calculate SIGNIFICAND
	while (i < BITS) {
		int idx = (int)(i / 32);
		bit = (x.data[idx] >> (31 - (i % 32))) & 1;
		discreteDivideBy2(temp);
		if (bit == 1) {
			_x = discreteSum(_x, temp);
		}

		i++;
	}

	// Multiply if 2^x or Divide if 2^-x
	for (int i = 0; i < abs(exponent); i++) {
		if (exponent >= 0) {
			discreteMultiplyBy2(_x);
		}
		else {
			discreteDivideBy2(_x);
		}
	}

	// Convert to string
	string str = "";
	string _temp;
	bit = (x.data[0] >> 31) & 1;
	if (bit == 1) str += "-";
	for (int i = 0; i < _x._int.size(); i++) {
		_temp = to_string(_x._int[i]);
		if (i != 0)
			while (_temp.size() < DIGITS) _temp.insert(_temp.begin(), '0');
		str += _temp;
	}
	str += ".";

	while ((_x._frc[_x._frc.size() - 1] % 10 == 0) && (_x._frc[_x._frc.size() - 1] != 0))
		_x._frc[_x._frc.size() - 1] /= 10;

	for (int i = 0; i < _x._frc.size(); i++) {
		if (_x._frc[i] == 0) continue;
		_temp = to_string(_x._frc[i]);
		if (i != _x._frc.size() - 1)
			while (_temp.size() < DIGITS) _temp.insert(_temp.begin(), '0');
		str += _temp;
	}

	if (str[str.size() - 1] == '.') str += "0";

	return str;
}

string QFloatBoolArrToBinStr(bool* bit) {
	string bin_str;

	for (int i = 0; i < BIT_COUNT; i++) {
		bin_str += bit[i];
	}

	return bin_str;
}


string QIntConversion(int p1, int p2, string operand) {
	string result;

	if (p1 == 2) {
		if (p2 == 2) {
			result = operand;
		}
		else {
			bool *bit = BinStrToBoolArr(operand);	// Binary string -> Bool*

			if (p2 == 10) {
				QInt qint = binToDecQInt(bit);		// Bool* -> QInt
				result = QIntToDecStr(qint);		// QInt -> Decimal string
			}
			else if (p2 == 16) {
				result = binToHex(bit);				// Bool* -> Hexadecimal string
			}

			delete[] bit;
		}
	}
	else if (p1 == 10) {
		if (p2 == 10) {
			result = operand;
		}
		else if (p2 == 2) {
			bool* bit = new bool[BIT_COUNT]();
			decStrToBinStr(operand, bit, BIT_COUNT);	// Decimal string -> Bool*
			result = QIntBoolArrToBinStr(bit);			// Bool* -> Binary string

			delete[] bit;
		}
		else if (p2 == 16) {
			QInt qint = DecStrToQInt(operand);	// Decimal string -> QInt
			result = decToHex(qint);			// QInt -> Hexadecimal string
		}
	}
	else if (p1 == 16) {
		if (p2 == 16) {
			result = operand;
		}
		else if (p2 == 2) {
			bool* bit = new bool[BIT_COUNT]();
			bit = HexToBin(operand);			// Hexadecimal string -> Bool*
			result = QIntBoolArrToBinStr(bit);	// Bool* -> Binary string

			delete[] bit;
		}
		else if (p2 == 10) {
			QInt qint = hexToDec(operand);	// Hexadecimal string -> QInt
			result = QIntToDecStr(qint);	// QInt -> Decimal string
		}
	}

	return result;
}

string QFloatConversion(int p1, int p2, string operand) {
	string result;

	if (p1 == 2 && p2 == 10) {
		bool* bit;

		bit = BinStrToBoolArr(operand);			// Binary string -> Bool*
		Qfloat qfloat = binToDecQfloat(bit);	// Bool* -> QFloat
		result = QFloatToFloatStr(qfloat);		// QFloat -> Float string

		delete[] bit;
	}
	else if (p1 == 10 && p2 == 2) {
		bool* bit = new bool[BIT_COUNT]();

		Qfloat qfloat = FloatStrToQFloat(operand);
		bit = decToBinQfloat(qfloat);			// Decimal string -> Bool*
		result = QFloatBoolArrToBinStr(bit);	// Bool* -> Binary string

		delete[] bit;
	}

	return result;
}

string QIntOperation(int p, string operation, string operand_1, string operand_2) {
	QInt result_qint;

	QInt op_1;

	if (p == 2) {
		bool* bit;

		bit = BinStrToBoolArr(operand_1);
		op_1 = binToDecQInt(bit);

		delete[] bit;
	}
	else if (p == 10) {
		op_1 = DecStrToQInt(operand_1);
	}
	else if (p == 16) {
		op_1 = hexToDec(operand_1);
	}


	if (operation == "~") {
		result_qint = ~op_1;
	}
	/*
	else if (operation == "<<" || operation == ">>" || operation == "rol" || operation == "ror") {
		int op_2 = stoi(operand_2);
		if (operation == "<<") {
			result_qint = op_1 << op_2;
		}
		else if (operation == ">>") {
			result_qint = op_1 >> op_2;
		}
		else if (operation == "rol") {
			result_qint = rol(op_1, op_2);
		}
		else {
			result_qint = ror(op_1, op_2);
		}
	}
	*/
	else {
		QInt op_2;

		if (p == 2) {
			bool* bit;

			bit = BinStrToBoolArr(operand_2);
			op_2 = binToDecQInt(bit);

			delete[] bit;
		}
		else if (p == 10) {
			op_2 = DecStrToQInt(operand_2);
		}
		else if (p == 16) {
			op_2 = hexToDec(operand_2);
		}
		

		if (operation == "+") {
			result_qint = op_1 + op_2;
		}
		else if (operation == "-") {
			result_qint = op_1 - op_2;
		}
		else if (operation == "*") {
			result_qint = op_1 * op_2;
		}
		else if (operation == "/") {
			result_qint = op_1 / op_2;
		}
		else if (operation == "&") {
			result_qint = op_1 & op_2;
		}
		else if (operation == "|") {
			result_qint = op_1 | op_2;
		}
		else if (operation == "^") {
			result_qint = op_1 ^ op_2;
		}
		else if (operation == "<<") {
			result_qint = op_1 << op_2;
		}
		else if (operation == ">>") {
			result_qint = op_1 >> op_2;
		}
		else if (operation == "rol") {
			result_qint = rol(op_1, op_2);
		}
		else {
			result_qint = ror(op_1, op_2);
		}
	}

	string result_string;
	result_string = QIntToDecStr(result_qint);
	return result_string;
}


void TestMode(char *inputFilename, char* outputFilename, int type) {
	ifstream fin;
	fin.open(inputFilename);
	if (!fin.is_open()) {
		return;
	}

	ofstream fout;
	fout.open(outputFilename);
	if (!fout.is_open()) {
		return;
	}

	string data_line;
	while (getline(fin, data_line)) {
		vector<string> data_list;
		int i = 0;

		while (i < data_line.size()) {
			while (data_line[i] == ' ' && i < data_line.size()) {
				i++;
			}

			if (i == data_line.size()) break;

			string data;
			while (data_line[i] != ' ' && i < data_line.size()) {
				data += data_line[i];
			}
			data_list.push_back(data);
		}

		if (data_list[0] != "2" && data_list[0] != "10" && data_list[0] != "16") {
			break;
		}
		string result;
		if (data_list.size() == 3) {
			if (data_list[1] == "2" || data_list[1] == "10" || data_list[1] == "16") {
				if (type == 1) {
					result = QIntConversion(stoi(data_list[0]), stoi(data_list[1]), data_list[2]);
				}
				else if (type == 2) {
					result = QFloatConversion(stoi(data_list[0]), stoi(data_list[1]), data_list[2]);
				}
			}
			else if (data_list[1] == "~") {
				result = QIntOperation(stoi(data_list[0]), data_list[1], data_list[2], "");
			}
		}
		else if (data_list.size() == 4) {
			result = QIntOperation(stoi(data_list[0]), data_list[2], data_list[1], data_list[3]);
		}

		fout << result << endl;
	}

	fout.close();
	fin.close();
}
