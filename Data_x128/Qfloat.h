#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#define DIGITS 8
#define BITS 128
#define SIGNIFICAND 112
#define EXPONENT 15

using namespace std;

struct Qfloat {
	int data[4] = {};
};

struct discrete {
	vector <int> _int;
	vector <int> _frc;
};

int multiply2(vector <int> &a);
int mod2(vector <int> &a);
bool isZero(vector <int> a);
void processIntergralPart(string intergral, vector <int> &_int, vector <bool> &binInt);
bool processFractionalPart(string fractional, vector <int> &_frac, vector <bool> &binFrac, vector <bool> binInt);
int checkUnderflow(vector <bool> binFrac);
void scanQfloat(Qfloat &x);
void printBinaryQfloat(Qfloat x);

Qfloat binToDecQFloat(bool *bit);
bool *decToBin(Qfloat x);


void discreteMultiplyBy2(discrete &x);
void discreteDivideBy2(discrete &x);
discrete discreteSum(discrete x, discrete y);
void printQfloat(Qfloat x);

void print(discrete x);