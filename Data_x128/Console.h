#pragma once

#include "QInt.h"
#include "Qfloat.h"
#include "Graphic.h"
#include <fstream>

enum class Mode {
	QINT,
	QFLOAT
};

enum class Base {
	BINARY,
	DECIMAL,
	HEXADECIMAL
};

static Mode _MODE_ = Mode::QINT;
static Base _BASE_ = Base::DECIMAL;

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

bool scanBinNumber(QInt& x, string str);

bool scanDecNumber(QInt& x, string dec_str);

bool scanHexNumber(QInt& x, string hex_str);

void printQInt(QInt x, Base base);


void consoleMode();

void menuHome();

void menuMode();

void menuQInt();

void menuExchangeBase();

void menuConvert();

void menuConvertToBin();
