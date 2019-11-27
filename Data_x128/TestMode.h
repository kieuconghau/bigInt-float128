#pragma once
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string QIntConversion(int p1, int p2, string operand);

string QFloatConversion(int p1, int p2, string operand);

string QIntBinaryOperation(int p, string operation, string operand_1, string operand_2);

void TestMode(char *inputFilename, char* outputFilename, int type);
