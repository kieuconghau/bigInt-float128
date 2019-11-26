#include "TestMode.h"

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
		if (data_list[1] == "2" || data_list[1] == "10" || data_list[1] == "16") {
			result = Conversion(stoi(data_list[0]), stoi(data_list[1]), data_list[2]);
		}
		else {
			result = BinaryOperation(stoi(data_list[0]), data_list[2], data_list[1], data_list[3]);
		}

		fout << result << endl;
	}

	fout.close();
	fin.close();
}
