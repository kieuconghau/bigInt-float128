#include "Console.h"

bool isNumber(string s) {
	if (s == "")
		return false;

	for (int i = 0; i < s.size(); ++i)
		if (s[i] < '0' || s[i] > '9')
			return false;
	return true;
}

bool isInRange(string s, int start, int end) {
	if (!isNumber(s))
		return false;

	int num = stoi(s);
	return num >= start && num <= end;
}

string getMode() {
	switch (_MODE_)
	{
	case Mode::QINT:
		return "QInt";
		break;
	case Mode::QFLOAT:
		return "QFloat";
		break;
	default:
		return "\aBug!!!!!";
		break;
	}
}

string getBase() {
	switch (_BASE_)
	{
	case Base::BINARY:
		return "Binary";
		break;
	case Base::DECIMAL:
		return "Decimal";
		break;
	case Base::HEXADECIMAL:
		return "Hexadecimal";
		break;
	default:
		return "\aBug!!!!!";
		break;
	}
}

void printStatus() {
	cout << " * Mode: " << getMode() << endl;
	cout << " * Base: " << getBase() << endl;
}

void printLine() {
	for (int i = 0; i < getConsoleWidth(); ++i)
		cout << "=";
	cout << endl;
}

void consoleMode() {
	textColor(Color::WHITE);

	/*===========================================*/
	menuMain();
}

void menuMain() {
	while (true) {
		string c;
		do {
			system("cls");
			printLine();
			cout << " Hello hooman!" << endl;
			printLine();
			cout << " 0. Exit" << endl;
			cout << " 1. Mode" << endl;
			cout << " 2. Help" << endl;
			printLine();
			cout << " Select: ";
			getline(cin, c);
		} while (!isInRange(c, 0, 2));

		if (c == "0") {
			return;
		}
		else if (c == "1") {
			menuMode();
		}
		else if (c == "2") {

		}
		else {
			cout << "\aBug!!!!!" << endl;
			return;
		}
	}
}

void menuMode() {
	while (true) {
		string c;
		do {
			system("cls");
			printLine();
			cout << " Mode >" << endl;
			printLine();
			cout << " 0. Back" << endl;
			cout << " 1. QInt" << endl;
			cout << " 2. QFloat" << endl;
			printLine();
			cout << " Select: ";
			getline(cin, c);
		} while (!isInRange(c, 0, 2));

		if (c == "0") {
			return;
		}
		else if (c == "1") {
			menuQInt();
		}
		else if (c == "2") {

		}
		else {
			cout << "\aBug!!!!!" << endl;
			return;
		}
	}
}

void menuQInt() {
	_MODE_ = Mode::QINT;

	while (true) {
		string c;
		do {
			system("cls");
			printLine();
			printStatus();
			printLine();
			cout << " Mode > QInt >" << endl;
			printLine();
			cout << " 0. Back" << endl;
			cout << " 1. Exchange base" << endl;
			cout << " 2. Convert" << endl;
			cout << " 3. Calculate" << endl;
			cout << " 4. Compare" << endl;
			printLine();
			cout << " Select: ";
			getline(cin, c);
		} while (!isInRange(c, 0, 4));

		if (c == "0") {
			return;
		}
		else if (c == "1") {
			menuExchangeBase();
		}
		else if (c == "2") {

		}
		else if (c == "3") {

		}
		else if (c == "4") {

		}
		else {
			cout << "\aBug!!!!!" << endl;
			return;
		}
	}
}

void menuExchangeBase() {
	while (true) {
		string c;
		do {
			system("cls");
			printLine();
			printStatus();
			printLine();
			cout << " Mode > QInt > Exchange base >" << endl;
			printLine();
			cout << " 0. Back" << endl;
			cout << " 1. Binary" << endl;
			cout << " 2. Decimal" << endl;
			cout << " 3. Hexadecimal" << endl;
			printLine();
			cout << " Select: ";
			getline(cin, c);
		} while (!isInRange(c, 0, 3));

		if (c == "0") {
			return;
		}
		else if (c == "1") {
			_BASE_ = Base::BINARY;
			return;
		}
		else if (c == "2") {
			_BASE_ = Base::DECIMAL;
			return;
		}
		else if (c == "3") {
			_BASE_ = Base::HEXADECIMAL;
			return;
		}
		else {
			cout << "\aBug!!!!!" << endl;
			return;
		}
	}
}

void menuConvert() {
	while (true) {
		string c;
		do {
			system("cls");
			printLine();
			printStatus();
			printLine();
			cout << " Mode > QInt > Convert" << endl;
			printLine();
			cout << " 0. Back" << endl;
			cout << " 1. To binary" << endl;
			cout << " 2. To decimal" << endl;
			cout << " 3. To hexadecimal" << endl;
			printLine();
			cout << " Select: ";
			getline(cin, c);
		} while (!isInRange(c, 0, 3));

		if (c == "0") {
			return;
		}
		else if (c == "1") {

		}
		else if (c == "2") {

		}
		else if (c == "3") {

		}
		else if (c == "4") {

		}
		else {
			cout << "\aBug!!!!!" << endl;
			return;
		}
	}
}