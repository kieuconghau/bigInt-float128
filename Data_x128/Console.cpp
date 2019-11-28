#include "Console.h"


/* Check if a string is a decimal number and in range [start, end] */
bool isInRange(string s, int start, int end) {
	if (!isNumber(s, Base::DECIMAL_))
		return false;

	if (s.size() >= 10)
		return false;

	int num = stoi(s);
	return num >= start && num <= end;
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


/* Get the relational operator's symbol: < or <= or > or >= or == */
string getRelationalOperatorSymbol(Relational cmp) {
	switch (cmp)
	{
	case Relational::LESS_:
		return "<";
	case Relational::LESS_EQUAL_:
		return "<=";
	case Relational::GREATER_:
		return ">";
	case Relational::GREATER_EQUAL_:
		return ">=";
	case Relational::EQUAL_:
		return "==";
	default:
		_BUG_LOG_ << "<string getRelationalOperatorSymbol(Relational rel);>" << endl;
		cout << "\a";
		return "Bug!!!!!";
	}
}


/* Get the arithmetic operator's symbol: + or - or * or / */
string getArithmeticOperatorSymbol(Arithmetic ari) {
	switch (ari)
	{
	case Arithmetic::ADD_:
		return "+";
	case Arithmetic::SUBSTRACT_:
		return "-";
	case Arithmetic::MULTIPLY_:
		return "*";
	case Arithmetic::DIVIDE_:
		return "/";
	default:
		_BUG_LOG_ << "<string getArithmeticOperatorSymbol(Arithmetic ari);>" << endl;
		cout << "\a";
		return "Bug!!!!!";
	}
}


/* Get the bitwise operator's symbol: & or | or ^ or ~ or >> or << or ROR or ROL */
string getBitwiseOperatorSymbol(Bitwise btw) {
	switch (btw)
	{
	case Bitwise::AND_:
		return "&";
	case Bitwise::OR_:
		return "|";
	case Bitwise::XOR_:
		return "^";
	case Bitwise::NOT_:
		return "~";
	case Bitwise::ARI_SHIFT_LEFT_:
		return "<<";
	case Bitwise::ARI_SHIFT_RIGHT_:
		return ">>";
	case Bitwise::ROTATE_LEFT_:
		return "rol";
	case Bitwise::ROTATE_RIGHT_:
		return "ror";
	default:
		_BUG_LOG_ << "<string getBitwiseOperatorSymbol(Bitwise btw);>" << endl;
		cout << "\a";
		return "Bug!!!!!";
	}
}


/* Display the current status (Mode + Base) */
void printStatus() {
	cout << " * Mode: ";
	textColor(_COLOR_STATUS_);
	cout << getMode() << endl;
	textColor(_COLOR_MAIN_);
	cout << " * Base: ";
	textColor(_COLOR_STATUS_);
	cout << getBase() << endl;
	textColor(_COLOR_MAIN_);
}


/* Display the notification about number status */
void printNotification(Notification noti) {
	textColor(_COLOR_NOTIFICATION_ERROR_);

	switch (noti)
	{
	case Notification::VALID_NUMBER_:
		textColor(_COLOR_NOTIFICATION_);
		cout << "The value is valid.";
		break;
	case Notification::NOT_NUMBER_:
		cout << "\aThe value is not a number. Please input a number in " << getBase() << " base.";
		break;
	case Notification::OVERFLOW_:
		cout << "\aThe value is overflow.";
		break;
	case Notification::UNDERFLOW_:
		cout << "\aThe value is underflow.";
		break;
	case Notification::DIVIDE_BY_ZERO_:
		cout << "\aCan not divide by zero.";
		break;
	case Notification::NOT_BIN_QFLOAT:
		cout << "\aThe value is invalid. Please input exactly " <<  BIT_COUNT << " bits.";
		break;
	case Notification::NONE_:
		textColor(_COLOR_NOTIFICATION_);
		cout << "...";
		break;
	default:
		_BUG_LOG_ << "<void printNotification(NumberStatus num_status);>";
		cout << "\a";
		break;
	}

	textColor(_COLOR_MAIN_);
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
Notification scanBinNumber(QInt& x, string bin_str) {
	if (!isNumber(bin_str, Base::BINARY_))	// Number in binary base?
		return Notification::NOT_NUMBER_;

	if (bin_str.size() > BIT_COUNT)			// Overflow?
		return Notification::OVERFLOW_;

	normalizeBinString(bin_str);

	bool* bit = new bool[BIT_COUNT]();		// Convert string to bool*
	for (int i = 0; i < BIT_COUNT; ++i)
		if (bin_str[i] == '1')
			bit[i] = 1;
	
	x = binToDecQInt(bit);					// Convert bool* to QInt
	
	delete[] bit;

	return Notification::VALID_NUMBER_;
}


/* Input a number in decimal base and check if it is valid and not overflow */
Notification scanDecNumber(QInt& x, string dec_str) {
	if (!isDecNumber(dec_str))				// Number in decimal base?
		return Notification::NOT_NUMBER_;

	bool* bit = new bool[BIT_COUNT]();		// Convert string to bool* and check not overflow
	bool is_not_overflow = decStrToBinStr(dec_str, bit, BIT_COUNT);

	if (!is_not_overflow)
		return Notification::OVERFLOW_;

	x = binToDecQInt(bit);					// Convert bool* to QInt

	delete[] bit;

	return Notification::VALID_NUMBER_;
}


/* Input a number in hexadecimal base and check if it is valid and not overflow */
Notification scanHexNumber(QInt& x, string hex_str) {
	if (!isNumber(hex_str, Base::HEXADECIMAL_))	// Number in hexadecimal base?
		return Notification::NOT_NUMBER_;

	if (hex_str.size() > BIT_COUNT / 4)			// Overflow?
		return Notification::OVERFLOW_;

	normalizeHexString(hex_str);

	x = hexToDec(hex_str);

	return Notification::VALID_NUMBER_;
}


/* Input a number in a correspoding base and check if it is valid and not overflow */
Notification scanNumber(QInt& x, string num, Base base) {
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
		return Notification::NOT_NUMBER_;
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


/* Main function */
void consoleMode() {
	zoomFullConsoleWindow();
	textColor(_COLOR_MAIN_);

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
			
			textColor(_COLOR_FUNCTION_);
			cout << " 0. Exit" << endl;
			cout << " 1. Mode" << endl;
			cout << " 2. Help" << endl;
			textColor(_COLOR_MAIN_);
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
			_BUG_LOG_ << "<void menuHome();>" << endl;
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
			
			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. QInt" << endl;
			cout << " 2. QFloat" << endl;
			textColor(_COLOR_MAIN_);
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
			menuQFloat();
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
	_BASE_ = Base::DECIMAL_;
	
	string choice;

	while (true) {
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
			
			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. Exchange base" << endl;
			cout << " 2. Convert" << endl;
			cout << " 3. Calculate" << endl;
			textColor(_COLOR_MAIN_);
			printEqualLine();
		
			cout << " Select: ";
			getline(cin, choice);
		} while (!isInRange(choice, 0, 3));

		if (choice == "0") {
			return;
		}
		else if (choice == "1") {
			menuExchangeBase();
		}
		else if (choice == "2") {
			menuConvert();
		}
		else if (choice == "3") {
			menuCalculate();
		}
		else {
			_BUG_LOG_ << "<void menuQInt();>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: Exchange the current base (_BASE_) */
void menuExchangeBase() {
	string choice;

	while (true) {
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

			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. Binary" << endl;
			cout << " 2. Decimal" << endl;
			cout << " 3. Hexadecimal" << endl;
			textColor(_COLOR_MAIN_);
			printEqualLine();
			
			cout << " Select: ";
			getline(cin, choice);
		} while (!isInRange(choice, 0, 3));

		if (choice == "0") {
			return;
		}
		else if (choice == "1") {
			_BASE_ = Base::BINARY_;
			return;
		}
		else if (choice == "2") {
			_BASE_ = Base::DECIMAL_;
			return;
		}
		else if (choice == "3") {
			_BASE_ = Base::HEXADECIMAL_;
			return;
		}
		else {
			_BUG_LOG_ << "<void menuExchangeBase();>" << endl;
			cout << "\a";
			return;
		}
	}
}

/* Menu: Covert */
void menuConvert() {
	string choice;

	while (true) {
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
			
			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. To Binary" << endl;
			cout << " 2. To Decimal" << endl;
			cout << " 3. To Hexadecimal" << endl;
			textColor(_COLOR_MAIN_);
			printEqualLine();
			
			cout << " Select: ";
			getline(cin, choice);
		} while (!isInRange(choice, 0, 3));

		if (choice == "0") {
			return;
		}
		else if (choice == "1") {
			menuConvert(Base::BINARY_);
		}
		else if (choice == "2") {
			menuConvert(Base::DECIMAL_);
		}
		else if (choice == "3") {
			menuConvert(Base::HEXADECIMAL_);
		}
		else {
			_BUG_LOG_ << "<void menuConvert();>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: Convert to the corresponding base */
void menuConvert(Base base) {
	QInt a;
	QInt b;
	Notification noti = Notification::NONE_;
	string choice;

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
			printTextAtMiddle(whereY(), title, _COLOR_TITLE_, true);
			textColor(_COLOR_MAIN_);
			printMinusLine();

			cout << endl;
			cout << " * B:  ";
			printNumber(b, _BASE_);		cout << endl;
			cout << endl;
			printMinusLine();

			cout << endl;
			cout << " * A:  ";
			textColor(_COLOR_ANSWER_);
			printNumber(a, base);		cout << endl;
			textColor(_COLOR_MAIN_);
			cout << endl;
			printMinusLine();

			cout << endl;
			cout << " * Notification: ";
			printNotification(noti);		cout << endl;
			cout << endl;
			printEqualLine();

			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. Input B" << endl;
			textColor(_COLOR_MAIN_);
			printEqualLine();

			cout << " Select: ";
			getline(cin, choice);
		} while (!isInRange(choice, 0, 1));

		if (choice == "0") {
			return;
		}
		else if (choice == "1") {
			printEqualLine();

			cout << " Please input B: ";
			string B_str;
			getline(cin, B_str);

			noti = scanNumber(b, B_str, _BASE_);
		}
		else {
			_BUG_LOG_ << "<void menuConvert(Base base);>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: Calculate (+, -, *, /, &, |, ^, ~, >>, <<, rol, ror) */
void menuCalculate() {
	string choice;

	while (true) {
		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QInt > Calculate >" << endl;
			printEqualLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printEqualLine();

			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. Arithmetic operators" << endl;
			cout << " 2. Relational operators" << endl;
			cout << " 3. Bitwise operators" << endl;
			textColor(_COLOR_MAIN_);
			printEqualLine();

			cout << " Select: ";
			getline(cin, choice);
		} while (!isInRange(choice, 0, 3));

		if (choice == "0") {
			return;
		}
		else if (choice == "1") {
			menuArithmeticOperators();
		}
		else if (choice == "2") {
			menuRelationalOperators();
		}
		else if (choice == "3") {
			menuBitwiseOperators();
		}
		else {
			_BUG_LOG_ << "<void menuCalculate();>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: Compare 2 QInt */
void menuRelationalOperators() {
	string choice;

	while (true) {
		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QInt > Calculate > Relational Operators >" << endl;
			printEqualLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printEqualLine();

			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. A = B <  C		(Less)" << endl;
			cout << " 2. A = B <= C		(Less or Equal)" << endl;
			cout << " 3. A = B >  C		(Greater)" << endl;
			cout << " 4. A = B >= C		(Greater or Equal)" << endl;
			cout << " 5. A = B == C		(Equal)" << endl;
			textColor(_COLOR_MAIN_);
			printEqualLine();

			cout << " Select: ";
			getline(cin, choice);
		} while (!isInRange(choice, 0, 5));

		if (choice == "0") {
			return;
		}
		else if (choice == "1") {
			menuRelationalOperators(Relational::LESS_);
		}
		else if (choice == "2") {
			menuRelationalOperators(Relational::LESS_EQUAL_);
		}
		else if (choice == "3") {
			menuRelationalOperators(Relational::GREATER_);
		}
		else if (choice == "4") {
			menuRelationalOperators(Relational::GREATER_EQUAL_);
		}
		else if (choice == "5") {
			menuRelationalOperators(Relational::EQUAL_);
		}
		else {
			_BUG_LOG_ << "<void menuRelationalOperators();>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: Compare 2 QInt with the corresponding operator */
void menuRelationalOperators(Relational rel) {
	bool a;
	QInt b;
	QInt c;
	Notification noti = Notification::NONE_;
	string choice;

	while (true) {
		switch (rel)
		{
		case Relational::LESS_:
			a = b < c;
			break;
		case Relational::LESS_EQUAL_:
			a = b <= c;
			break;
		case Relational::GREATER_:
			a = b > c;
			break;
		case Relational::GREATER_EQUAL_:
			a = b >= c;
			break;
		case Relational::EQUAL_:
			a = b == c;
			break;
		default:
			_BUG_LOG_ << "<void menuRelationalOperators(Relational rel);>" << endl;
			cout << "\a";
			return;
		}
		
		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QInt > Calculate > Relational Operators > A = B " << getRelationalOperatorSymbol(rel) << " C >" << endl;
			printEqualLine();

			string title = "[ A (Bool) = B (" + getBase(_BASE_) + ") " + getRelationalOperatorSymbol(rel) + " C (" + getBase(_BASE_) + ") ]";
			printTextAtMiddle(whereY(), title, _COLOR_TITLE_, true);
			textColor(_COLOR_MAIN_);
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
			textColor(_COLOR_ANSWER_);
			a ? cout << "True" << endl : cout << "False" << endl;
			textColor(_COLOR_MAIN_);
			cout << endl;
			printMinusLine();

			cout << endl;
			cout << " * Notification: ";
			printNotification(noti);		cout << endl;
			cout << endl;
			printEqualLine();

			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. Input B" << endl;
			cout << " 2. Input C" << endl;
			textColor(_COLOR_MAIN_);
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

			noti = scanNumber(b, B_str, _BASE_);
		}
		else if (choice == "2") {
			printEqualLine();

			cout << " Please input C: ";
			string C_str;
			getline(cin, C_str);

			noti = scanNumber(c, C_str, _BASE_);
		}
		else {
			_BUG_LOG_ << "<void menuRelationalOperators(Relational rel);>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: Arithmetic Operators (+ - * /) */
void menuArithmeticOperators() {
	string choice;

	while (true) {
		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QInt > Calculate > Arithmetic Operators >" << endl;
			printEqualLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printEqualLine();

			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. A = B + C	(Add)" << endl;
			cout << " 2. A = B - C	(Substract)" << endl;
			cout << " 3. A = B * C	(Multiply)" << endl;
			cout << " 4. A = B / C	(Divide)" << endl;
			textColor(_COLOR_MAIN_);
			printEqualLine();

			cout << " Select: ";
			getline(cin, choice);
		} while (!isInRange(choice, 0, 4));

		if (choice == "0") {
			return;
		}
		else if (choice == "1") {
			menuArithmeticOperators(Arithmetic::ADD_);
		}
		else if (choice == "2") {
			menuArithmeticOperators(Arithmetic::SUBSTRACT_);
		}
		else if (choice == "3") {
			menuArithmeticOperators(Arithmetic::MULTIPLY_);
		}
		else if (choice == "4") {
			menuArithmeticOperators(Arithmetic::DIVIDE_);
		}
		else {
			_BUG_LOG_ << "<void menuArithmeticOperators();>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: arithmetic operators */
void menuArithmeticOperators(Arithmetic ari) {
	QInt a;
	QInt b;
	QInt c;
	Notification noti = Notification::NONE_;
	string choice;

	while (true) {
		switch (ari)
		{
		case Arithmetic::ADD_:
			a = b + c;
			if ((isPositive(b) && isPositive(c) && isNegative(a)) ||
				(isNegative(b) && isNegative(c) && isPositive(a)))
				noti = Notification::OVERFLOW_;
			break;
		case Arithmetic::SUBSTRACT_:
			a = b - c;
			if ((isPositive(b) && isNegative(c) && isNegative(a)) ||
				(isNegative(b) && isPositive(c) && isPositive(a)))
				noti = Notification::OVERFLOW_;
			break;
		case Arithmetic::MULTIPLY_:
			a = b * c;
			if (!isZero(b) && !isZero(c) && !(a / b == c))
				noti = Notification::OVERFLOW_;
			break;
		case Arithmetic::DIVIDE_:
			a = b / c;
			if (isZero(c))
				noti = Notification::DIVIDE_BY_ZERO_;
			break;
		default:
			break;
		}

		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QInt > Calculate > Arithmetic Operators > A = B " << getArithmeticOperatorSymbol(ari) << " C >" << endl;
			printEqualLine();

			string title = "[ A (" + getBase(_BASE_) + ") = B (" + getBase(_BASE_) + ") " + getArithmeticOperatorSymbol(ari) + " C (" + getBase(_BASE_) + ") ]";
			printTextAtMiddle(whereY(), title, _COLOR_TITLE_, true);
			textColor(_COLOR_MAIN_);
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
			textColor(_COLOR_ANSWER_);
			printNumber(a, _BASE_);		cout << endl;
			textColor(_COLOR_MAIN_);
			cout << endl;
			printMinusLine();

			cout << endl;
			cout << " * Notification: ";
			printNotification(noti);		cout << endl;
			cout << endl;
			printEqualLine();

			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. Input B" << endl;
			cout << " 2. Input C" << endl;
			textColor(_COLOR_MAIN_);
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

			noti = scanNumber(b, B_str, _BASE_);
		}
		else if (choice == "2") {
			printEqualLine();

			cout << " Please input C: ";
			string C_str;
			getline(cin, C_str);

			noti = scanNumber(c, C_str, _BASE_);
		}
		else {
			_BUG_LOG_ << "<void menuArithmeticOperators(Arithmetic ari);>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: bitwise operators */
void menuBitwiseOperators() {
	string choice;

	while (true) {
		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QInt > Calculate > Bitwise Operators >" << endl;
			printEqualLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printEqualLine();

			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. A = B & C		(And)" << endl;
			cout << " 2. A = B | C		(Or)" << endl;
			cout << " 3. A = B ^ C		(Xor)" << endl;
			cout << " 4. A = ~B		(Not)" << endl;
			cout << " 5. A = B << C		(Arithmetic Shift Left)" << endl;
			cout << " 6. A = B >> C		(Arithmetic Shift Right)" << endl;
			cout << " 7. A = B rol C		(Rotate Left)" << endl;
			cout << " 8. A = B ror C		(Rotate Right)" << endl;
			textColor(_COLOR_MAIN_);
			printEqualLine();

			cout << " Select: ";
			getline(cin, choice);
		} while (!isInRange(choice, 0, 8));

		if (choice == "0") {
			return;
		}
		else if (choice == "1") {
			menuBitwiseOperators(Bitwise::AND_);
		}
		else if (choice == "2") {
			menuBitwiseOperators(Bitwise::OR_);
		}
		else if (choice == "3") {
			menuBitwiseOperators(Bitwise::XOR_);
		}
		else if (choice == "4") {
			menuBitwiseOperator_NOT();
		}
		else if (choice == "5") {
			menuBitwiseOperators(Bitwise::ARI_SHIFT_LEFT_);
		}
		else if (choice == "6") {
			menuBitwiseOperators(Bitwise::ARI_SHIFT_RIGHT_);
		}
		else if (choice == "7") {
			menuBitwiseOperators(Bitwise::ROTATE_LEFT_);
		}
		else if (choice == "8") {
			menuBitwiseOperators(Bitwise::ROTATE_RIGHT_);
		}
		else {
			_BUG_LOG_ << "<void menuBitwiseOperators();>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: bitwise operators */
void menuBitwiseOperators(Bitwise btw) {
	QInt a;
	QInt b;
	QInt c;
	Notification noti = Notification::NONE_;
	string choice;

	while (true) {
		switch (btw)
		{
		case Bitwise::AND_:
			a = b & c;
			break;
		case Bitwise::OR_:
			a = b | c;
			break;
		case Bitwise::XOR_:
			a = b ^ c;
			break;
		case Bitwise::NOT_:
			_BUG_LOG_ << "<void menuBitwiseOperators(Bitwise btw);>" << endl;
			cout << "\a";
			return;
		case Bitwise::ARI_SHIFT_LEFT_:
			a = b << c;
			break;
		case Bitwise::ARI_SHIFT_RIGHT_:
			a = b >> c;
			break;
		case Bitwise::ROTATE_LEFT_:
			a = rol(b, c);
			break;
		case Bitwise::ROTATE_RIGHT_:
			a = ror(b, c);
			break;
		default:
			_BUG_LOG_ << "<void menuBitwiseOperators(Bitwise btw);>" << endl;
			cout << "\a";
			return;
		}

		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QInt > Calculate > Bitwise Operators > A = B " << getBitwiseOperatorSymbol(btw) << " C >" << endl;
			printEqualLine();

			string title = "[ A (" + getBase(_BASE_) + ") = B (" + getBase(_BASE_) + ") " + getBitwiseOperatorSymbol(btw) + " C (" + getBase(_BASE_) + ") ]";
			printTextAtMiddle(whereY(), title, _COLOR_TITLE_, true);
			textColor(_COLOR_MAIN_);
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
			textColor(_COLOR_ANSWER_);
			printNumber(a, _BASE_);		cout << endl;
			textColor(_COLOR_MAIN_);
			cout << endl;
			printMinusLine();

			cout << endl;
			cout << " * Notification: ";
			printNotification(noti);		cout << endl;
			cout << endl;
			printEqualLine();

			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. Input B" << endl;
			cout << " 2. Input C" << endl;
			textColor(_COLOR_MAIN_);
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

			noti = scanNumber(b, B_str, _BASE_);
		}
		else if (choice == "2") {
			printEqualLine();

			cout << " Please input C: ";
			string C_str;
			getline(cin, C_str);

			noti = scanNumber(c, C_str, _BASE_);
		}
		else {
			_BUG_LOG_ << "<void menuBitwiseOperators(Bitwise btw);>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: bitwise operator NOT */
void menuBitwiseOperator_NOT() {
	QInt a;
	QInt b;
	Notification noti = Notification::NONE_;
	string choice;

	while (true) {
		a = ~b;

		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QInt > Calculate > Bitwise Operators > A = ~B " << endl;
			printEqualLine();

			string title = "[ A (" + getBase(_BASE_) + ") = ~B (" + getBase(_BASE_) + ") ]";
			printTextAtMiddle(whereY(), title, _COLOR_TITLE_, true);
			textColor(_COLOR_MAIN_);
			printMinusLine();

			cout << endl;
			cout << " * B:  ";
			printNumber(b, _BASE_);		cout << endl;
			cout << endl;
			printMinusLine();

			cout << endl;
			cout << " * A:  ";
			textColor(_COLOR_ANSWER_);
			printNumber(a, _BASE_);		cout << endl;
			textColor(_COLOR_MAIN_);
			cout << endl;
			printMinusLine();

			cout << endl;
			cout << " * Notification: ";
			printNotification(noti);		cout << endl;
			cout << endl;
			printEqualLine();

			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. Input B" << endl;
			textColor(_COLOR_MAIN_);
			printEqualLine();

			cout << " Select: ";
			getline(cin, choice);
		} while (!isInRange(choice, 0, 1));

		if (choice == "0") {
			return;
		}
		else if (choice == "1") {
			printEqualLine();

			cout << " Please input B: ";
			string B_str;
			getline(cin, B_str);

			noti = scanNumber(b, B_str, _BASE_);
		}
		else {
			_BUG_LOG_ << "<void menuBitwiseOperator_NOT();>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: QFloat mode */
void menuQFloat() {
	_MODE_ = Mode::QFLOAT_;
	_BASE_ = Base::DECIMAL_;

	string choice;

	while (true) {
		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QFloat >" << endl;
			printEqualLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printEqualLine();

			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. Exchange base" << endl;
			cout << " 2. Convert" << endl;
			textColor(_COLOR_MAIN_);
			printEqualLine();

			cout << " Select: ";
			getline(cin, choice);
		} while (!isInRange(choice, 0, 2));

		if (choice == "0") {
			return;
		}
		else if (choice == "1") {
			menuExchangeBaseQFloat();
		}
		else if (choice == "2") {
			menuConvertQFloat();
		}
		else {
			_BUG_LOG_ << "<void menuQFloat();>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: exchange base (qfloat) */
void menuExchangeBaseQFloat() {
	string choice;

	while (true) {
		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QFloat > Exchange base >" << endl;
			printEqualLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printEqualLine();

			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. Binary" << endl;
			cout << " 2. Decimal" << endl;
			textColor(_COLOR_MAIN_);
			printEqualLine();

			cout << " Select: ";
			getline(cin, choice);
		} while (!isInRange(choice, 0, 2));

		if (choice == "0") {
			return;
		}
		else if (choice == "1") {
			_BASE_ = Base::BINARY_;
			return;
		}
		else if (choice == "2") {
			_BASE_ = Base::DECIMAL_;
			return;
		}
		else {
			_BUG_LOG_ << "<void menuExchangeBaseQFloat();>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: convert (qfloat) */
void menuConvertQFloat() {
	string choice;

	while (true) {
		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QFloat > Convert >" << endl;
			printEqualLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printMinusLine();

			cout << endl << endl;
			printEqualLine();

			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. To Binary" << endl;
			cout << " 2. To Decimal" << endl;
			textColor(_COLOR_MAIN_);
			printEqualLine();

			cout << " Select: ";
			getline(cin, choice);
		} while (!isInRange(choice, 0, 2));

		if (choice == "0") {
			return;
		}
		else if (choice == "1") {
			menuConvertQFloat(Base::BINARY_);
		}
		else if (choice == "2") {
			menuConvertQFloat(Base::DECIMAL_);
		}
		else {
			_BUG_LOG_ << "<void menuConvertQFloat();>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Menu: convert (qfloat) */
void menuConvertQFloat(Base base) {
	Qfloat x;
	Notification noti = Notification::NONE_;
	string choice;

	while (true) {
		do {
			system("cls");
			printEqualLine();
			printStatus();
			printEqualLine();

			cout << " Mode > QFloat > Convert > To " << getBase(base) + " >" << endl;
			printEqualLine();

			string title = "[ B (" + getBase(_BASE_) + ") -> A (" + getBase(base) + ") ]";
			printTextAtMiddle(whereY(), title, _COLOR_TITLE_, true);
			textColor(_COLOR_MAIN_);
			printMinusLine();

			cout << endl;
			cout << " * B:  ";
			printNumber(x, _BASE_);		cout << endl;
			cout << endl;
			printMinusLine();

			cout << endl;
			cout << " * A:  ";
			textColor(_COLOR_ANSWER_);
			printNumber(x, base);		cout << endl;
			textColor(_COLOR_MAIN_);
			cout << endl;
			printMinusLine();

			cout << endl;
			cout << " * Notification: ";
			printNotification(noti);		cout << endl;
			cout << endl;
			printEqualLine();

			textColor(_COLOR_FUNCTION_);
			cout << " 0. Back" << endl;
			cout << " 1. Input B" << endl;
			textColor(_COLOR_MAIN_);
			printEqualLine();

			cout << " Select: ";
			getline(cin, choice);
		} while (!isInRange(choice, 0, 1));

		if (choice == "0") {
			return;
		}
		else if (choice == "1") {
			printEqualLine();

			cout << " Please input B: ";
			string B_str;
			getline(cin, B_str);

			noti = scanNumber(x, B_str, _BASE_);
		}
		else {
			_BUG_LOG_ << "<void menuConvert(Base base);>" << endl;
			cout << "\a";
			return;
		}
	}
}


/* Display a qfloat number with the corresponding base */
void printNumber(Qfloat x, Base base, int column, int row) {
	switch (base)
	{
	case Base::BINARY_:
		printBinNumber(x, column, row);
		break;
	case Base::DECIMAL_:
		printDecNumber(x, column, row);
		break;
	default:
		_BUG_LOG_ << "<void printNumber(Qfloat x, Base base, int column, int row);>" << endl;
		cout << "\a";
		break;
	}
}


/* Input a qfloat number with the correspoding base */
Notification scanNumber(Qfloat& x, string num, Base base) {
	switch (base)
	{
	case Base::BINARY_:
		return scanBinNumber(x, num);
	case Base::DECIMAL_:
		return scanDecNumber(x, num);
	default:
		_BUG_LOG_ << "<Notification scanNumber(Qfloat& x, string num, Base base);>" << endl;
		cout << "\a";
		return Notification::NONE_;
	}
}


/* Display a qfloat number in binary base */
void printBinNumber(Qfloat x, int column, int row) {
	bool* bin = decToBinQfloat(x);

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


/* Display a qfloat number in decimal base */
void printDecNumber(Qfloat x, int column, int row) {
	gotoXY(column, row);
	printQfloat(x);
}


/* Input a qfloat number in binary base */
Notification scanBinNumber(Qfloat& x, string bin_str) {
	if (!isBinQFloat(bin_str))
		return Notification::NOT_BIN_QFLOAT;

	Qfloat zero;
	x = zero;

	bool* bit = new bool[BIT_COUNT]();		// Convert string to bool*
	for (int i = 0; i < BIT_COUNT; ++i)
		if (bin_str[i] == '1')
			bit[i] = 1;

	x = binToDecQfloat(bit);					// Convert bool* to QInt

	delete[] bit;

	return Notification::VALID_NUMBER_;
}


/* Input a qfloat number in decimal base */
Notification scanDecNumber(Qfloat& x, string dec_str) {
	if (!isDecQFloat(dec_str))
		return Notification::NOT_NUMBER_;
	
	Qfloat zero;
	x = zero;

	// ==== PROCESS SIGN ====
	bool sign = (dec_str[0] == '-'); //
	if (sign) dec_str = dec_str.substr(1, dec_str.size() - 1);
	x.data[0] = x.data[0] | (sign << 31);


	// ==== SPLIT PART ====
	int idx_dot = 0; // index of "."
	while (idx_dot < dec_str.size() && dec_str[idx_dot] != '.') idx_dot++;  // find index of "."
	if (idx_dot == dec_str.size())dec_str += ".0";
	string integral = dec_str.substr(0, idx_dot); // integral part of dec_str
	string fractional = dec_str.substr(idx_dot + 1, dec_str.size() - idx_dot); // fractional part of dec_str

	// ==== PROCESS INTEGRAL PART ====
	int nInt = (int)((integral.size() % DIGITS == 0) ? (integral.size() / DIGITS) : (integral.size() / DIGITS) + 1); // calc range
	vector <int> _int(nInt);
	vector <bool> binInt;
	processIntegralPart(integral, _int, binInt);

	// ==== PROCESS FRACTIONAL PART ====
	int nFrac = (int)((fractional.size() % DIGITS == 0) ? (fractional.size() / DIGITS) : (fractional.size() / DIGITS) + 1); // calc range
	vector <int> _frac(nFrac);
	vector <bool> binFrac;
	processFractionalPart(fractional, _frac, binFrac, binInt);

	if (nFrac == 1 && nInt == 1 && binFrac.size() == 0 && binInt.size() == 0)
		return Notification::VALID_NUMBER_; // Qfloat 0

	// ==== PROCESS EXPONENT ====
	int floating = 0;
	int exponent = 0;
	if (integral == "0") { // check if 0.xxxx
		floating = checkUnderflow(binFrac);
		if (!floating) { // check if Underflow
			//cout << "Error: Underflow" << endl;
			return Notification::UNDERFLOW_;
		}
	}
	else floating = binInt.size() - 1; // dot move to left
	exponent = (floating > (-pow(2, EXPONENT - 1) + 2)) ? floating + (pow(2, EXPONENT - 1) - 1) : 0; /* Check exponent is normal or denormalized */

	if (exponent > (pow(2, 15) - 1)) {	// check if Overflow
		//cout << "Error: Overflow" << endl;
		return Notification::OVERFLOW_;
	}

	vector <int> ex;
	ex.push_back(exponent);

	for (int i = 15; i >= 1 && !isZero(ex); i--) {
		if (mod2(ex)) {
			x.data[0] = x.data[0] | (1 << (31 - i));
		}
	}

	// ==== LAST PROCESS ====
	int bit = 16;
	for (int i = 1; i < binInt.size(); i++) {
		int idx = (int)(bit / 32); // index of x.data[]
		x.data[idx] = x.data[idx] | (binInt[i] << (31 - (bit - 32 * idx)));
		bit++;
	}

	int start = 0;
	if (integral == "0") {
		start = (floating > (-pow(2, EXPONENT - 1) + 2)) ? (-floating) : (-pow(2, EXPONENT - 1) + 2 - 1);
	}
	for (int i = start; (bit <= BITS) && (i < binFrac.size()); i++) {
		int idx = (int)(bit / 32); // index of x.data[]
		x.data[idx] = x.data[idx] | (binFrac[i] << (31 - (bit - 32 * idx)));
		bit++;
	}

	return Notification::VALID_NUMBER_;
}


/* Check if a string is a binary qfloat (128 bits)*/
bool isBinQFloat(string bin_str) {
	if (bin_str == "")
		return false;

	if (bin_str.size() != BIT_COUNT)
		return false;

	for (int i = 0; i < BIT_COUNT; ++i)
		if (!isDigit(bin_str[i], Base::BINARY_))
			return false;
	return true;
}


/* Check if a string is a decimal qfloat (a.b or a) */
bool isDecQFloat(string dec_str) {
	if (dec_str == "")
		return false;

	int i = 0;
	if (dec_str[0] == '-')
		i = 1;

	int dot_count = 0;
	for ( ; i < dec_str.size(); ++i) {
		if (dec_str[i] == '.')
			++dot_count;
		else if (!isDigit(dec_str[i], Base::DECIMAL_))
			return false;
	}

	if (dot_count > 1)
		return false;

	if (dec_str[0] == '.')		// .b
		return false;
	if (dec_str[0] == '-' && dec_str[1] == '.')		// -.b
		return false;
	if (dec_str[dec_str.size() - 1] == '.')			// a.
		return false;

	return true;
}
