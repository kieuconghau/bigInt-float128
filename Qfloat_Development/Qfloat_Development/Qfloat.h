/*

	Hi! I'm Buu. If there's any bug, that's because Buu is sleepy. Don't mind xD

*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#define DIGITS 8
#define BITS 128

using namespace std;

struct Qfloat {
	int data[4] = {};
};

int multiply2(int *a, int n);
int mod2(int *a, int n);
bool isZero(int *a, int n);
void processIntergralPart(string intergral, int nInt, int *_int, vector <bool> &binInt);
bool processFractionalPart(string fractional, int nFrac, int *_frac, vector <bool> &binFrac, vector <bool> binInt);

void scanQfloat(Qfloat &x);
void printBinaryQfloat(Qfloat x);