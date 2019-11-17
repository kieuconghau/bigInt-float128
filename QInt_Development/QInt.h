#pragma once

#include <iostream>
#include <string>
#include <cstdint>
using namespace std;


#define BYTE_SIZE 16									// BigInt 16 bytes
#define BIT_SIZE BYTE_SIZE * 8							// 128
#define PART_SIZE 9										// Depend on the type of QInt.data

#define DATA_COUNT BYTE_SIZE / sizeof(uint32_t)			// 4
#define UINT_BIT_SIZE sizeof(uint32_t) * 8				// 32


struct QInt {
	uint32_t data[DATA_COUNT] = {};
};


bool isNegative(QInt x);


void scanQInt(QInt& x);

bool decStrToBinStr(string str, bool* bit, int bit_size);

string decStrDivide2(string str);

bool decStrMod2(string str);


void printQInt(QInt x);

string decStrMultiply2(string str);

string decStrAddDecStr(string str1, string str2);


bool* decToBin(QInt x);

void printBin(QInt x);

QInt binToDec(bool* bit);


QInt operator+(QInt x, QInt y);


QInt operator&(QInt x, QInt y);

QInt operator|(QInt x, QInt y);

QInt operator^(QInt x, QInt y);

QInt operator~(QInt x);


QInt operator<<(QInt x, size_t shift_bit_num);

QInt operator>>(QInt x, size_t shift_bit_num);

QInt rol(QInt x, size_t shift_bit_num);

QInt ror(QInt x, size_t rotate_bit_num);
