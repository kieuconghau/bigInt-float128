#pragma once
#include <iostream>
#include <string>

using namespace std;

struct QInt {
	int data[4] = {};
};

int mod2(int *a, int n);
bool isZero(int *a, int n);
void scanQInt(QInt &x);

void printBinaryQInt(QInt x);