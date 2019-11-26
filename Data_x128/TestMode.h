#pragma once
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string Conversion(int p1, int p2, string operand);

string BinaryOperation(int p, string operation, string operand_1, string operand_2);

void TestMode(char *inputFilename, char* outputFilename, int type);
