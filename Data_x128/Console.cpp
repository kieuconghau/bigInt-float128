#include "Console.h"

/* Check if a string is a decimal number and in range [start, end] */
bool isInRange(string s, int start, int end) {
	if (!isNumber(s, Base::DECIMAL))
		return false;

	int num = stoi(s);
	return num >= start && num <= end;
}


/* Get the current Mode: OInt or QFloat */
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


/* Get the current Base: Bin or Dec or Hex */
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


/* Display the current status (Mode + Base) */
void printStatus() {
	cout << " * Mode: " << getMode() << endl;
	cout << " * Base: " << getBase() << endl;
}


/* Display the divider */
void printLine() {
	string line(getConsoleWidth(), '=');
	cout << line << endl;
}


/* Check if a character is a binary digit */
bool isBinDigit(char c) {
	return c == '0' || c == '1';
}


/* Check if a character is a decimal digit */
bool isDecDigit(char c) {
	return c >= '0' && c <= '9';
}


/* Check if a character is a hexadecimal digit */
bool isHexDigit(char c) {
	return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F');
}


/* Check if a character is a valid digit in the corresponding base */
bool isDigit(char c, Base base) {
	switch (base)
	{
	case Base::BINARY:
		return isBinDigit(c);
	case Base::DECIMAL:
		return isDecDigit(c);
	case Base::HEXADECIMAL:
		return isHexDigit(c);
	default:
		_BUG_LOG_ << "\a<bool isValidDigit(char c, Base base);>" << endl;
		return false;
	}
}


/* Check if a string is a valid binary string */
bool isBinNumber(string bin_str) {
	if (bin_str == "")
		return false;

	for (int i = 0; i < bin_str.size(); ++i)
		if (!isDigit(bin_str[i], Base::BINARY))
			return false;
	return true;
}


/* Check if a string is a valid decimal string */
bool isDecNumber(string dec_str) {
	if (dec_str == "")
		return false;

	int i = 0;
	if (dec_str[0] == '-')
		i = 1;

	for ( ; i < dec_str.size(); ++i)
		if (!isDigit(dec_str[i], Base::DECIMAL))
			return false;
	return true;
}


/* Check if a string is a valid hexadecimal string */
bool isHexNumber(string hex_str) {
	if (hex_str == "")
		return false;

	for (int i = 0; i < hex_str.size(); ++i)
		if (!isDigit(hex_str[i], Base::HEXADECIMAL))
			return false;
	return true;
}


/* Check if a string is a valid number in the correspoding base */
bool isNumber(string num, Base base) {
	switch (base)
	{
	case Base::BINARY:
		return isBinNumber(num);
	case Base::DECIMAL:
		return isDecNumber(num);
	case Base::HEXADECIMAL:
		return isHexNumber(num);
	default:
		_BUG_LOG_ << "\a<bool isNumber(string num, Base base);>" << endl;
		return false;
	}
}


/* Input a number in binary base and check if it is overflow */
bool scanBinNumber(QInt x, string str) {

}


void printQInt(QInt x, Base base) {
	string res;

	switch (base)
	{
	case Base::BINARY:
		printBin(x);
		break;
	case Base::DECIMAL:
		printQInt(x);
		break;
	case Base::HEXADECIMAL:
		cout << decToHex(x) << endl;
		break;
	default:
		cout << "\aBug!!!!! <getQInt>" << endl;
		break;
	}
}

/* Main function */
void consoleMode() {
	textColor(Color::WHITE);

	_BUG_LOG_.open(_BUG_LOG_FILENAME_);
	
	if (!_BUG_LOG_.is_open()) {
		cout << "\aCan not create " << _BUG_LOG_FILENAME_ << "!" << endl;
		return;
	}

	menuHome();
	_BUG_LOG_.close();
}

void menuHome() {
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
			_BUG_LOG_ << "\a<void menuMain();>" << endl;
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
			_BUG_LOG_ << "\a<void menuMode();>" << endl;
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
			menuConvert();
		}
		else if (c == "3") {

		}
		else if (c == "4") {

		}
		else {
			_BUG_LOG_ << "\a<void menuQInt()>" << endl;
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
			_BUG_LOG_ << "\a<void menuExchangeBase()>" << endl;
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
			menuConvertToBin();
		}
		else if (c == "2") {

		}
		else if (c == "3") {

		}
		else if (c == "4") {

		}
		else {
			_BUG_LOG_ << "\a<void menuConvert()>" << endl;
			return;
		}
	}
}

void menuConvertToBin() {
	QInt a;
	QInt b;

	string c;
	while (true) {
		do {
			system("cls");
			printLine();
			printStatus();
			printLine();
			cout << " Mode > QInt > Convert > To binary" << endl;
			printLine();
			cout << " 0. Back" << endl;
			cout << " 1. Input B" << endl;
			printLine();
			cout << " Convert B (" << getBase() << ") to A (Binary): A <- B" << endl << endl;
			cout << " B: ";
			printQInt(b, _BASE_);
			printLine();
			cout << "A: ";
			printQInt(a, Base::BINARY);
			printLine();
			cout << " Select: ";
			getline(cin, c);
		} while (!isInRange(c, 0, 1));

		if (c == "0") {
			return;
		}
		else if (c == "1") {
			printLine();
			cout << " Input B: ";
			scanQInt(b);
			a = b;
		}
		else {
			_BUG_LOG_ << "\a<void menuConvertToBin()>" << endl;
			return;
		}
	}
}