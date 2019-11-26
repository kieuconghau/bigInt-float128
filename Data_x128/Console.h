#pragma once

#include "QInt.h"
#include "Qfloat.h"
#include "Graphic.h"

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


bool isNumber(string s);

bool isInRange(string s, int start, int end);

string getMode();

string getBase();

void printStatus();

void printLine();


void consoleMode();

void menuMain();

void menuMode();

void menuQInt();

void menuExchangeBase();

void menuConvert();
