#pragma once

#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

#define BYTE 16			// BigInt 16 bytes
#define PART_SIZE 9

struct QInt {
	uint32_t data[BYTE / sizeof(uint32_t)] = {};
};

void scanQInt(QInt& x);

bool decStrToBinStr(string str, bool* bit, int bit_size);

string decStrDivide2(string str);

bool decStrMod2(string str);

void printQInt(QInt x);

string decStrMultiple2(string str);

string decStrAddDecStr(string str1, string str2);

bool* decToBin(QInt x);

QInt binToDec(bool* bit);

QInt& operator<<(QInt& x, size_t i);