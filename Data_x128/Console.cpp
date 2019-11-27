#include "Console.h"

/*====================================================================================================*/
/*												   SUPPORT                                            */
/*====================================================================================================*/

/* Check if a string is a decimal number and in range [start, end] */
bool isInRange(string s, int start, int end) {
	if (!isNumber(s, Base::DECIMAL_))
		return false;

	return s >= to_string(start) && s <= to_string(end);
}


/* Get mode's name: OInt or QFloat */
string getMode(Mode mode) {
	switch (mode)
	{
	case Mode::QINT_:
		return "QInt";
	case Mode::QFLOAT_:
		return "QFloat";
	default:
		_BUG_LOG_ << "<string getMode();>" << endl;
		cout << "\a";
		return "Bug!!!!!";
	}
}


/* Get base's name: Binary or Decimal or Hexadecimal */
string getBase(Base base) {
	switch (base)
	{
	case Base::BINARY_:
		return "Binary";
		break;
	case Base::DECIMAL_:
		return "Decimal";
		break;
	case Base::HEXADECIMAL_:
		return "Hexadecimal";
		break;
	default:
		_BUG_LOG_ << "<sting getBase();>" << endl;
		cout << "\a";
		return "Bug!!!!!";
	}
}


/* Get comparison's symbol: < or <= or > or >= or == */
string getComparisonSymbol(Comparison cmp) {
	switch (cmp)
	{
	case Comparison::LESS_:
		return "<";
	case Comparison::LESS_EQUAL_:
		return "<=";
	case Comparison::GREATER_:
		return ">";
	case Comparison::GREATER_EQUAL_:
		return ">=";
	case Comparison::EQUAL_:
		return "==";
	default:
		_BUG_LOG_ << "<string getComparisonSymbol(Comparison cmp);>" << endl;
		cout << "\a";
		return "Bug!!!!!";
	}
}


/* Display the current status (Mode + Base) */
void printStatus() {
	cout << " * Mode: " << getMode() << endl;
	cout << " * Base: " << getBase() << endl;
}


/* Display the notification about number status */
void printNotification(NumberStatus num_status) {
	switch (num_status)
	{
	case NumberStatus::VALID_:
		cout << "The value is valid.";
		break;
	case NumberStatus::INVALID_:
		cout << "\aThe value is invalid. Please input a number in " << getBase() << " base.";
		break;
	case NumberStatus::OVERFLOW_:
		cout << "\aThe value is overflow.";
		break;
	default:
		_BUG_LOG_ << "<void printNotification(NumberStatus num_status);>";
		cout << "\a";
		break;
	}
}

/* Display the divider (Equal) */
void printEqualLine() {
	string line(getConsoleWidth(), '=');
	cout << line << endl;
}


/* Display the divider (Underscore) */
void printMinusLine() {
	string line(getConsoleWidth(), '-');
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
	case Base::BINARY_:
		return isBinDigit(c);
	case Base::DECIMAL_:
		return isDecDigit(c);
	case Base::HEXADECIMAL_:
		return isHexDigit(c);
	default:
		_BUG_LOG_ << "<bool isValidDigit(char c, Base base);>" << endl;
		cout << "\a";
		return false;
	}
}


/* Check if a string is a valid binary string */
bool isBinNumber(string bin_str) {
	if (bin_str == "")
		return false;

	for (int i = 0; i < bin_str.size(); ++i)
		if (!isDigit(bin_str[i], Base::BINARY_))
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
		if (!isDigit(dec_str[i], Base::DECIMAL_))
			return false;
	return true;
}


/* Check if a string is a valid hexadecimal string */
bool isHexNumber(string hex_str) {
	if (hex_str == "")
		return false;

	for (int i = 0; i < hex_str.size(); ++i)
		if (!isDigit(hex_str[i], Base::HEXADECIMAL_))
			return false;
	return true;
}


/* Check if a string is a valid number in the correspoding base */
bool isNumber(string num, Base base) {
	switch (base)
	{
	case Base::BINARY_:
		return isBinNumber(num);
	case Base::DECIMAL_:
		return isDecNumber(num);
	case Base::HEXADECIMAL_:
		return isHexNumber(num);
	default:
		_BUG_LOG_ << "<bool isNumber(string num, Base base);>" << endl;
		cout << "\a";
		return false;
	}
}


/* Fill a string with zero at front */
void fillStrWithZeroAtFront(string& str, int size) {
	string temp(size, '0');

	int i = size - 1;
	int j = str.size() - 1;

	while (i >= 0 && j >= 0) {
		temp[i] = str[j];
		--i;
		--j;
	}

	str = temp;
}

/* Normalize a binary string (size = 128) <bin_str must be valid> */
void normalizeBinString(string& bin_str) {
	fillStrWithZeroAtFront(bin_str, BIT_COUNT);
}


/* Normalize a hexadecimal string (size = 32) <hex_str must be valid> */
void normalizeHexString(string& hex_str) {
	fillStrWithZeroAtFront(hex_str, BIT_COUNT / 4);
}


/* Denormalize a binary string (erase all 0s at front) */
void denormalizeBinString(string& bin_str) {
	while (bin_str[0] == '0')
		bin_str.erase(bin_str.begin());
}


/* Denormalize a hexadecimal string (erase all 0s at front) */
void denormalizeHexString(string& hex_string) {
	while (hex_string[0] == '0')
		hex_string.erase(hex_string.begin());
}


/* Input a number in binary base and check if it is valid and not overflow */
NumberStatus scanBinNumber(QInt& x, string bin_str) {
	if (!isNumber(bin_str, Base::BINARY_))	// Number in binary base?
		return NumberStatus::INVALID_;

	if (bin_str.size() > BIT_COUNT)			// Overflow?
		return NumberStatus::OVERFLOW_;

	normalizeBinString(bin_str);

	bool* bit = new bool[BIT_COUNT]();		// Convert string to bool*
	for (int i = 0; i < BIT_COUNT; ++i)
		if (bin_str[i] == '1')
			bit[i] = 1;
	
	x = binToDecQInt(bit);					// Convert bool* to QInt
	
	delete[] bit;

	return NumberStatus::VALID_;
}


/* Input a number in decimal base and check if it is valid and not overflow */
NumberStatus scanDecNumber(QInt& x, string dec_str) {
	if (!isDecNumber(dec_str))				// Number in decimal base?
		return NumberStatus::INVALID_;

	bool* bit = new bool[BIT_COUNT]();		// Convert string to bool* and check not overflow
	bool is_not_overflow = decStrToBinStr(dec_str, bit, BIT_COUNT);

	if (!is_not_overflow)
		return NumberStatus::OVERFLOW_;

	x = binToDecQInt(bit);					// Convert bool* to QInt

	delete[] bit;

	return NumberStatus::VALID_;
}


/* Input a number in hexadecimal base and check if it is valid and not overflow */
NumberStatus scanHexNumber(QInt& x, string hex_str) {
	if (!isNumber(hex_str, Base::HEXADECIMAL_))	// Number in hexadecimal base?
		return NumberStatus::INVALID_;

	if (hex_str.size() > BIT_COUNT / 4)			// Overflow?
		return NumberStatus::OVERFLOW_;

	normalizeHexString(hex_str);

	x = hexToDec(hex_str);

	return NumberStatus::VALID_;
}


/* Input a number in a correspoding base and check if it is valid and not overflow */
NumberStatus scanNumber(QInt& x, string num, Base base) {
	switch (base)
	{
	case Base::BINARY_:
		return scanBinNumber(x, num);
	case Base::DECIMAL_:
		return scanDecNumber(x, num);
	case Base::HEXADECIMAL_:
		return scanHexNumber(x, num);
	default:
		_BUG_LOG_ << "<bool scanNumber(QInt& x, string num, Base base);>" << endl;
		cout << "\a";
		return NumberStatus::INVALID_;
	}
}


/* Print a number in binary base */
void printBinNumber(QInt x, int column, int row) {
	bool* bin = decToBin(x);

	for (int i = 0; i < DATA_COUNT; ++i) {
		gotoXY(column, row + i);
		
		for (int j = 0; j < UINT_BIT_SIZE; ++j) {
			cout << bin[UINT_BIT_SIZE * i + j];
			if (j % 8 == 7)
				cout << " ";
		}
	}

	delete[] bin;
}


/* Print a number in decimal base */
void printDecNumber(QInt x, int column, int row) {
	gotoXY(column, row);
	printQInt(x);
}


/* Print a number in hexadecimal base */
void printHexNumber(QInt x, int column, int row) {
	gotoXY(column, row);
	cout << decToHex(x);
}


/* Print a number in a correspoding base */
void printNumber(QInt x, Base base, int column, int row) {
	switch (base)
	{
	case Base::BINARY_:
		printBinNumber(x, column, row);
		break;
	case Base::DECIMAL_:
		printDecNumber(x, column, row);
		break;
	case Base::HEXADECIMAL_:
		printHexNumber(x, column, row);
		break;
	default:
		_BUG_LOG_ << "<void printNumber(QInt x, Base base, int column, int row);>" << endl;
		cout << "\a";
		break;
	}
}

/*====================================================================================================*/
/*                                                   MENU                                             */
/*====================================================================================================*/

/* Main function */
void consoleMode() {
	zoomFullConsoleWindow();
	textColor(_COLOR_);

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
			printEqualLine();
			
			cout << " Hello hooman!" << endl;
			printEqualLine();
			
			cout << " 0. Exit" << endl;
			cout << " 1. Mode" << endl;
			cout << " 2. Help" << endl;
			printEqualLine();
			
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
			_BUG_LOG_ << "<void menuMain();>" << endl;
			cout << "\a";
			return;
		}
	}
}

void menuMode() {
	while (true) {
		string c;
		do {
			system("cls");
			printEqualLine();
			
			cout << " Mode >" << endl;
			printEqualLine();
			
			cout << " 0. Back" << endl;
			cout << " 1. QInt" << endl;
			cout << " 2. QFloat" << endl;
			printEqualLine();
			
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
			_BUG_LOG_ << "<void menuMode();>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: QInt mode */
void menuQInt() {
	_MODE_ = Mode::QINT_;

	while (true) {
		string c;
		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();
			
			cout << " Mode > QInt >" << endl;
			printEqualLine();
			
			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printEqualLine();
			
			cout << " 0. Back" << endl;
			cout << " 1. Exchange base" << endl;
			cout << " 2. Convert" << endl;
			cout << " 3. Calculate" << endl;
			cout << " 4. Compare" << endl;
			printEqualLine();
		
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
			menuCompare();
		}
		else {
			_BUG_LOG_ << "<void menuQInt()>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: Exchange the current base (_BASE_) */
void menuExchangeBase() {
	while (true) {
		string c;
		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();
			
			cout << " Mode > QInt > Exchange base >" << endl;
			printEqualLine();
			
			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printEqualLine();

			cout << " 0. Back" << endl;
			cout << " 1. Binary" << endl;
			cout << " 2. Decimal" << endl;
			cout << " 3. Hexadecimal" << endl;
			printEqualLine();
			
			cout << " Select: ";
			getline(cin, c);
		} while (!isInRange(c, 0, 3));

		if (c == "0") {
			return;
		}
		else if (c == "1") {
			_BASE_ = Base::BINARY_;
			return;
		}
		else if (c == "2") {
			_BASE_ = Base::DECIMAL_;
			return;
		}
		else if (c == "3") {
			_BASE_ = Base::HEXADECIMAL_;
			return;
		}
		else {
			_BUG_LOG_ << "<void menuExchangeBase()>" << endl;
			cout << "\a";
			return;
		}
	}
}

/* Menu: Covert */
void menuConvert() {
	while (true) {
		string c;
		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();
			
			cout << " Mode > QInt > Convert >" << endl;
			printEqualLine();
			
			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printEqualLine();
			
			cout << " 0. Back" << endl;
			cout << " 1. To Binary" << endl;
			cout << " 2. To Decimal" << endl;
			cout << " 3. To Hexadecimal" << endl;
			printEqualLine();
			
			cout << " Select: ";
			getline(cin, c);
		} while (!isInRange(c, 0, 3));

		if (c == "0") {
			return;
		}
		else if (c == "1") {
			menuConvert(Base::BINARY_);
		}
		else if (c == "2") {
			menuConvert(Base::DECIMAL_);
		}
		else if (c == "3") {
			menuConvert(Base::HEXADECIMAL_);
		}
		else {
			_BUG_LOG_ << "<void menuConvert()>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: Convert to the corresponding base */
void menuConvert(Base base) {
	QInt a;
	QInt b;
	NumberStatus num_status = NumberStatus::VALID_;

	string c;
	while (true) {
		a = b;

		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QInt > Convert > To " << getBase(base) + " >" << endl;
			printEqualLine();

			string title = "[ B (" + getBase(_BASE_) + ") -> A (" + getBase(base) + ") ]";
			printTextAtMiddle(whereY(), title, Color::CYAN, true);
			textColor(_COLOR_);
			printMinusLine();

			cout << endl;
			cout << " * B:  ";
			printNumber(b, _BASE_);		cout << endl;
			cout << endl;
			printMinusLine();

			cout << endl;
			cout << " * A:  ";
			printNumber(a, base);		cout << endl;
			cout << endl;
			printMinusLine();

			cout << endl;
			cout << " * Notification: ";
			printNotification(num_status);		cout << endl;
			cout << endl;
			printEqualLine();

			cout << " 0. Back" << endl;
			cout << " 1. Input B" << endl;
			printEqualLine();

			cout << " Select: ";
			getline(cin, c);
		} while (!isInRange(c, 0, 1));

		if (c == "0") {
			return;
		}
		else if (c == "1") {
			printEqualLine();

			cout << " Please input B: ";
			string B_str;
			getline(cin, B_str);

			num_status = scanNumber(b, B_str, _BASE_);
		}
		else {
			_BUG_LOG_ << "<void menuConvertToBin()>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: Compare 2 QInt */
void menuCompare() {
	while (true) {
		string c;
		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QInt > Compare >" << endl;
			printEqualLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printEqualLine();

			cout << " 0. Back" << endl;
			cout << " 1. A = B <  C" << endl;
			cout << " 2. A = B <= C" << endl;
			cout << " 3. A = B >  C" << endl;
			cout << " 4. A = B >= C" << endl;
			cout << " 5. A = B == C" << endl;
			printEqualLine();

			cout << " Select: ";
			getline(cin, c);
		} while (!isInRange(c, 0, 5));

		if (c == "0") {
			return;
		}
		else if (c == "1") {
			menuCompare(Comparison::LESS_);
		}
		else if (c == "2") {
			menuCompare(Comparison::LESS_EQUAL_);
		}
		else if (c == "3") {
			menuCompare(Comparison::GREATER_);
		}
		else if (c == "4") {
			menuCompare(Comparison::GREATER_EQUAL_);
		}
		else if (c == "5") {
			menuCompare(Comparison::EQUAL_);
		}
		else {
			_BUG_LOG_ << "<void menuQInt()>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: Compare 2 QInt with the corresponding operator */
void menuCompare(Comparison cmp) {
	bool a = 0;
	QInt b;
	QInt c;
	NumberStatus num_status = NumberStatus::VALID_;
	string choice;

	while (true) {
		switch (cmp)
		{
		case Comparison::LESS_:
			a = b < c;
			break;
		case Comparison::LESS_EQUAL_:
			a = b <= c;
			break;
		case Comparison::GREATER_:
			a = b > c;
			break;
		case Comparison::GREATER_EQUAL_:
			a = b >= c;
			break;
		case Comparison::EQUAL_:
			a = b == c;
			break;
		default:
			_BUG_LOG_ << "<void menuCompare(Comparison cmp);>" << endl;
			cout << "\a";
			return;
		}
		
		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QInt > Compare > A = B " << getComparisonSymbol(cmp) << " C >" << endl;
			printEqualLine();

			string title = "[ A (Bool) = B (" + getBase(_BASE_) + ") " + getComparisonSymbol(cmp) + " C (" + getBase(_BASE_) + ") ]";
			printTextAtMiddle(whereY(), title, Color::CYAN, true);
			textColor(_COLOR_);
			printMinusLine();

			cout << endl;
			cout << " * B:  ";
			printNumber(b, _BASE_);		cout << endl;
			cout << endl;

			cout << " * C:  ";
			printNumber(c, _BASE_);		cout << endl;
			cout << endl;
			printMinusLine();

			cout << endl;
			cout << " * A:  ";
			a ? cout << "True" << endl : cout << "False" << endl;
			cout << endl;
			printMinusLine();

			cout << endl;
			cout << " * Notification: ";
			printNotification(num_status);		cout << endl;
			cout << endl;
			printEqualLine();

			cout << " 0. Back" << endl;
			cout << " 1. Input B" << endl;
			cout << " 2. Input C" << endl;
			printEqualLine();

			cout << " Select: ";
			getline(cin, choice);
		} while (!isInRange(choice, 0, 2));

		if (choice == "0") {
			return;
		}
		else if (choice == "1") {
			printEqualLine();

			cout << " Please input B: ";
			string B_str;
			getline(cin, B_str);

			num_status = scanNumber(b, B_str, _BASE_);
		}
		else if (choice == "2") {
			printEqualLine();

			cout << " Please input C: ";
			string C_str;
			getline(cin, C_str);

			num_status = scanNumber(c, C_str, _BASE_);
		}
		else {
			_BUG_LOG_ << "<void menuConvertToBin()>" << endl;
			cout << "\a";
			return;
		}
	}
}