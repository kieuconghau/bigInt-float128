#pragma once
#include <fstream>
#include <string>
#include <vector>
using namespace std;

QInt DecStrToQInt(string dec_str);

string QIntToDecStr(QInt x);

bool* BinStrToBoolArr(string bin_str);

string BoolArrToBinStr(bool* bit);

QInt HexToDec(string hex);

bool* HexToBin(string hex);


string QIntConversion(int p1, int p2, string operand);

string QFloatConversion(int p1, int p2, string operand);

string QIntOperation(int p, string operation, string operand_1, string operand_2);

void TestMode(char *inputFilename, char* outputFilename, int type);
