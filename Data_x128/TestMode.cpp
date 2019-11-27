#include "TestMode.h"
#include "QInt.h"

string QIntConversion(int p1, int p2, string operand) {
	string result;

	if (p1 == 2) {
		if (p2 == 2) {
			result = operand;
		}
		else {
			bool* bit = new bool[BIT_COUNT]();
			// bit = BinStrToBoolArr(operand)	// Binary string -> Bool*

			if (p2 == 10) {
				QInt qint = binToDec(bit);		// Bool* -> QInt
				// result = QIntToDecStr(qint)	// QInt -> Decimal string
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
			// result = BoolArrToBinStr(bit)			// Bool* -> Binary string

			delete[] bit;
		}
		else if (p2 == 16) {
			QInt qint;
			// qint = DecStrToQInt(operand)		// Decimal string -> QInt
			result = decToHex(qint);			// QInt -> Hexadecimal string
		}
	}
	else if (p1 == 16) {
		if (p2 == 16) {
			result = operand;
		}
		else if (p2 == 2) {
			bool* bit = new bool[BIT_COUNT]();
			// bit = HexToBin(operand)			// Hexadecimal string -> Bool*
			// result = BoolArrToBinStr(bit)	// Bool* -> Binary string

			delete[] bit;
		}
		else if (p2 == 10) {
			// QInt qint = HexToDec(operand)	// Hexadecimal string -> QInt
			// result = QIntToDecStr(qint)		// QInt -> Decimal string
		}
	}

	return result;
}

string QIntOperation(int p, string operation, string operand_1, string operand_2) {
	QInt result_qint;

	QInt op_1;

	if (p == 2) {
		bool* bit = new bool[BIT_COUNT]();
		// bit = BinStrToBoolArr(operand_1)
		op_1 = binToDec(bit);
		delete[] bit;
	}
	else if (p == 10) {
		// op_1 = DecStrToQInt(operand_1)
	}
	else if (p == 16) {
		// op_1 = HexToDec(operand_1)
	}


	if (operation == "~") {
		result_qint = ~op_1;
	}
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
	else {
		QInt op_2;

		if (p == 2) {
			bool* bit = new bool[BIT_COUNT]();
			// bit = BinStrToBoolArr(operand_2)
			op_2 = binToDec(bit);
			delete[] bit;
		}
		else if (p == 10) {
			// op_2 = DecStrToQInt(operand_2)
		}
		else if (p == 16) {
			// op_2 = HexToDec(operand_2)
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
	}

	string result_string;
	// result_string = QIntToDecStr(result_qint)
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
