#pragma once

#include "QInt.h"
#include "Qfloat.h"
#include "Graphic.h"
#include <fstream>

enum class Mode {
	QINT_,
	QFLOAT_
};

enum class Base {
	BINARY_,
	DECIMAL_,
	HEXADECIMAL_
};

enum class NumberStatus {
	VALID_,					// VALID_ = !(INVALID_ or OVERFLOW_)
	INVALID_,
	OVERFLOW_
};


static Mode _MODE_ = Mode::QINT_;
static Base _BASE_ = Base::DECIMAL_;

static ofstream _BUG_LOG_;
static string _BUG_LOG_FILENAME_ = "BugLog.txt";


bool isInRange(string s, int start, int end);

string getMode();

string getBase();

void printStatus();

void printLine();

bool isBinNumber(string bin);

bool isDecNumber(string dec_str);

bool isHexNumber(string hex_str);

bool isNumber(string num, Base base);

void fillStrWithZeroAtFront(string& str, int size);

void normalizeBinString(string& bin_str);

void normalizeHexString(string& hex_str);

void denormalizeBinString(string& bin_str);

void denormalizeHexString(string& hex_string);

NumberStatus scanBinNumber(QInt& x, string str);

NumberStatus scanDecNumber(QInt& x, string dec_str);

NumberStatus scanHexNumber(QInt& x, string hex_str);

NumberStatus scanNumber(QInt& x, string num, Base base);

void printBinNumber(QInt x, int column = whereX(), int row = whereY());

void printQInt(QInt x, Base base);


void consoleMode();

void menuHome();

void menuMode();

void menuQInt();

void menuExchangeBase();

void menuConvert();

void menuConvertToBin();


