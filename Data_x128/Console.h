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
	UNDERFLOW_,
	DIVIDE_BY_ZERO_,
	NOT_BIN_QFLOAT,
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

static Color _COLOR_MAIN_ = Color::WHITE;
static Color _COLOR_TITLE_ = Color::BLUE;
static Color _COLOR_FUNCTION_ = Color::BLUE;
static Color _COLOR_ANSWER_ = Color::CYAN;
static Color _COLOR_NOTIFICATION_ = Color::GREEN;
static Color _COLOR_NOTIFICATION_ERROR_ = Color::RED;
static Color _COLOR_STATUS_ = Color::YELLOW;

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


bool isBinNumber(string bin_str);

bool isDecNumber(string dec_str);

bool isHexNumber(string hex_str);

bool isNumber(string num, Base base);


void fillStrWithZeroAtFront(string& str, int size);

void normalizeBinString(string& bin_str);

void normalizeHexString(string& hex_str);

void denormalizeBinString(string& bin_str);

void denormalizeHexString(string& hex_string);


Notification scanBinNumber(QInt& x, string bin_str);

Notification scanDecNumber(QInt& x, string dec_str);

Notification scanHexNumber(QInt& x, string hex_str);

Notification scanNumber(QInt& x, string num, Base base);


void printBinNumber(QInt x, int column = whereX(), int row = whereY());

void printDecNumber(QInt x, int column = whereX(), int row = whereY());

void printHexNumber(QInt x, int column = whereX(), int row = whereY());

void printNumber(QInt x, Base base, int column = whereX(), int row = whereY());


void consoleMode();		// MAIN

void menuHome();

void menuMode();

void menuAbout();


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


void menuQFloat();

void menuExchangeBaseQFloat();

void menuConvertQFloat();

void menuConvertQFloat(Base base);


void printNumber(Qfloat x, Base base, int column = whereX(), int row = whereY());

Notification scanNumber(Qfloat& x, string num, Base base);

void printBinNumber(Qfloat x, int column = whereX(), int row = whereY());

void printDecNumber(Qfloat x, int column = whereX(), int row = whereY());

Notification scanBinNumber(Qfloat& x, string bin_str);

Notification scanDecNumber(Qfloat& x, string dec_str);

bool isBinQFloat(string bin_str);

bool isDecQFloat(string dec_str);

