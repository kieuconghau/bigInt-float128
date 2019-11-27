#include "TestMode.h"
#include "QInt.h"
#include "Qfloat.h"

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

QInt HexToDec(string hex) {
	QInt res;

	int i = hex.size() - 1;
	int j = BIT_COUNT - 1;
	uint32_t temp;

	while (i >= 0 && j >= 0) {
		temp = hex[i] >= '0' && hex[i] <= '9' ? hex[i] - '0' : hex[i] - 'A' + 10;
		res.data[j / 32] |= temp << (31 - j % 32);		// 0, 4, 8, 12, 16, 20, 24, 28

		--i;
		j -= 4;
	}

	return res;
}

bool* HexToBin(string hex) {
	QInt x = HexToDec(hex);
	
	return decToBin(x);
}


Qfloat FloatStrToQFloat(string float_str) {

}

string QFloatToFloatStr(Qfloat x) {

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
			bool* bit = new bool[BIT_COUNT]();
			bit = BinStrToBoolArr(operand);		// Binary string -> Bool*

			if (p2 == 10) {
				QInt qint = binToDecQInt(bit);		// Bool* -> QInt
				result = QIntToDecStr(qint);	// QInt -> Decimal string
			}
			else if (p2 == 16) {
				result = binToHex(bit);			// Bool* -> Hexadecimal string
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
			QInt qint = HexToDec(operand);	// Hexadecimal string -> QInt
			result = QIntToDecStr(qint);	// QInt -> Decimal string
		}
	}

	return result;
}

string QFloatConversion(int p1, int p2, string operand) {
	string result;

	if (p1 == 2 && p2 == 10) {

	}
	else if (p1 == 10 && p2 == 2) {

	}

	return result;
}

string QIntOperation(int p, string operation, string operand_1, string operand_2) {
	QInt result_qint;

	QInt op_1;

	if (p == 2) {
		bool* bit = new bool[BIT_COUNT]();
		bit = BinStrToBoolArr(operand_1);
		op_1 = binToDecQInt(bit);
		delete[] bit;
	}
	else if (p == 10) {
		op_1 = DecStrToQInt(operand_1);
	}
	else if (p == 16) {
		op_1 = HexToDec(operand_1);
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
			bool* bit = new bool[BIT_COUNT]();
			bit = BinStrToBoolArr(operand_2);
			op_2 = binToDecQInt(bit);
			delete[] bit;
		}
		else if (p == 10) {
			op_2 = DecStrToQInt(operand_2);
		}
		else if (p == 16) {
			op_2 = HexToDec(operand_2);
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
	fout.open(inputFilename);
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
