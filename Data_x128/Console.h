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

enum class Notification {
	VALID_NUMBER_,					// VALID_NUMBER_ = !(NOT_NUMBER_ or OVERFLOW_ or DIVIDE_BY_ZERO_)
	NOT_NUMBER_,
	OVERFLOW_,
	DIVIDE_BY_ZERO_,
	NONE_
};

enum class Relational {
	LESS_,
	LESS_EQUAL_,
	GREATER_,
	GREATER_EQUAL_,
	EQUAL_
};

enum class Arithmetic {
	ADD_,
	SUBSTRACT_,
	MULTIPLY_,
	DIVIDE_
};

enum class Bitwise {
	AND_,
	OR_,
	XOR_,
	NOT_,
	ARI_SHIFT_LEFT_,
	ARI_SHIFT_RIGHT_,
	ROTATE_LEFT_,
	ROTATE_RIGHT_
};

static Color _COLOR_ = Color::WHITE;

static Mode _MODE_ = Mode::QINT_;
static Base _BASE_ = Base::DECIMAL_;

static ofstream _BUG_LOG_;
static string _BUG_LOG_FILENAME_ = "BugLog.txt";


bool isInRange(string s, int start, int end);

string getMode(Mode mode = _MODE_);

string getBase(Base base = _BASE_);

string getRelationalOperatorSymbol(Relational cmp);

string getArithmeticOperatorSymbol(Arithmetic ari);

string getBitwiseOperatorSymbol(Bitwise btw);

void printStatus();

void printNotification(Notification noti);

void printEqualLine();

void printMinusLine();

bool isBinNumber(string bin);

bool isDecNumber(string dec_str);

bool isHexNumber(string hex_str);

bool isNumber(string num, Base base);

void fillStrWithZeroAtFront(string& str, int size);

void normalizeBinString(string& bin_str);

void normalizeHexString(string& hex_str);

void denormalizeBinString(string& bin_str);

void denormalizeHexString(string& hex_string);

Notification scanBinNumber(QInt& x, string str);

Notification scanDecNumber(QInt& x, string dec_str);

Notification scanHexNumber(QInt& x, string hex_str);

Notification scanNumber(QInt& x, string num, Base base);

void printBinNumber(QInt x, int column = whereX(), int row = whereY());

void printDecNumber(QInt x, int column = whereX(), int row = whereY());

void printHexNumber(QInt x, int column = whereX(), int row = whereY());

void printNumber(QInt x, Base base, int column = whereX(), int row = whereY());


void consoleMode();

void menuHome();

void menuMode();

void menuQInt();

void menuExchangeBase();

void menuConvert();

void menuConvert(Base base);

void menuCalculate();

void menuRelationalOperators();

void menuRelationalOperators(Relational rel);

void menuArithmeticOperators();

void menuArithmeticOperators(Arithmetic ari);

void menuBitwiseOperators();

void menuBitwiseOperators(Bitwise btw);

void menuBitwiseOperator_NOT();
