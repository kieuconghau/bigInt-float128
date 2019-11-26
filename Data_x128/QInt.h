#pragma once

#include <iostream>
#include <string>
#include <cstdint>
using namespace std;


#define BYTE_COUNT 16										// BigInt 16 bytes
#define BIT_COUNT BYTE_COUNT * 8							// 128

#define DATA_COUNT BYTE_COUNT / sizeof(uint32_t)			// 4
#define UINT_BIT_SIZE sizeof(uint32_t) * 8					// 32


struct QInt {
	uint32_t data[DATA_COUNT] = {};

	QInt& operator=(QInt const & x);
};


bool isNegative(QInt x);

bool isPositive(QInt x);

bool isZero(QInt x);

bool isMinQInt(QInt x);


bool isOne(string str);

bool isZero(string str);


void scanQInt(QInt& x);

bool decStrToBinStr(string str, bool* bit, int bit_size);

string posDecStrDivideBy2(string str);

bool posDecStrMod2(string str);


void printQInt(QInt x);

string posDecStrMultiplyBy2(string str);

string posDecStrAddPosDecStr(string str1, string str2);


bool* decToBin(QInt x);

void printBin(QInt x);

QInt binToDecQInt(bool* bit);


string binToHex(bool* bit);

string decToHex(QInt x);

QInt hexToDec(string hex);


QInt operator+(QInt x, QInt y);

QInt operator-(QInt x, QInt y);

QInt operator*(QInt x, QInt y);

QInt operator/(QInt x, QInt y);


bool operator==(QInt x, QInt y);

bool operator>(QInt x, QInt y);

bool operator<=(QInt x, QInt y);

bool operator<(QInt x, QInt y);

bool operator>=(QInt x, QInt y);


QInt operator&(QInt x, QInt y);

QInt operator|(QInt x, QInt y);

QInt operator^(QInt x, QInt y);

QInt operator~(QInt x);


QInt operator<<(QInt x, int shift_bit_num);

QInt logicalShiftLeft(QInt x, int shift_bit_num);

QInt operator>>(QInt x, int shift_bit_num);

QInt logicalShiftRight(QInt x, int shift_bit_num);

QInt rol(QInt x, int shift_bit_num);

QInt ror(QInt x, int rotate_bit_num);

