#include "Qfloat.h"

int multiply2(vector <int> &a) {
	int r = 0;

	for (int i = a.size() - 1; i >= 0; i--) {
		a[i] *= 2;
		a[i] += r;
		r = a[i] / pow(10, DIGITS);
		if (r != 0) a[i] -= r * pow(10, DIGITS);
	}

	return r;
}

int mod2(vector <int> &a) {
	int result = a[a.size() - 1] % 2;
	a[a.size() - 1] /= 2;

	for (int i = a.size() - 2; i >= 0; i--) {
		int r = a[i] % 2;
		a[i] = a[i] / 2;
		a[i + 1] += r * pow(10, DIGITS) / 2;
	}

	return result;
}

bool isZero(vector <int> a) {
	for (int i = a.size() - 1; i >= 0; i--) {
		if (a[i] != 0) return false;
	}
	return true;
}

void processIntergralPart(string intergral, vector <int> &_int, vector <bool> &binInt) {
	string d;

	for (int i = _int.size() - 1; i >= 1; i--) { // backward
		d = intergral.substr(intergral.size() - (_int.size() - i) * DIGITS, DIGITS); // split 8 digits
		_int[i] = stoi(d);
	}
	d = intergral.substr(0, intergral.size() - (_int.size() - 1) * DIGITS);
	_int[0] = stoi(d);

	while (!isZero(_int)) {
		binInt.insert(binInt.begin(), mod2(_int));
	}
}

bool processFractionalPart(string fractional, vector <int> &_frac, vector <bool> &binFrac, vector <bool> binInt) {
	string d;

	if (_frac.size() > 1) {
		for (int i = 0; i < _frac.size() - 1; i++) {
			d = fractional.substr(i*DIGITS, DIGITS);
			_frac[i] = stoi(d);
		}
		d = fractional.substr((_frac.size() - 1)*DIGITS, fractional.size() - (_frac.size() - 1)*DIGITS);
		while (d.size() < DIGITS) d += '0'; // fill in d to get 8 digits
		_frac[_frac.size() - 1] = stoi(d);
	}
	else {
		while (fractional.size() < DIGITS) fractional += '0';
		_frac[0] = stoi(fractional);
	}

	int limit = pow(2, EXPONENT - 1) - 2 + SIGNIFICAND;
	while (((limit - (binInt.size() - 1) - binFrac.size()) > 0) && !isZero(_frac)) {
		binFrac.insert(binFrac.end(),multiply2(_frac));
	}

	return (binFrac.size() == 0);
}

int checkUnderflow(vector <bool> binFrac) {
	int floating = 0;
	for (int i = 0; !binFrac[i]; i++) 
		floating--;
	floating--;
	return (floating < -(pow(2, EXPONENT - 1) - 2 + SIGNIFICAND))? 0: floating;
}

void scanQfloat(Qfloat &x) {
	string str;
	cout << "x = "; cin >> str; getchar();

	// ==== PROCESS SIGN ====
	bool sign = (str[0] == '-'); //
	if (sign) str = str.substr(1, str.size() - 1);
	x.data[0] = x.data[0] | (sign << 31);


	// ==== SPLIT PART ====
	int idx_dot = 0; // index of "."
	while (idx_dot < str.size() && str[idx_dot] != '.') idx_dot++;  // find index of "."
	if (idx_dot == str.size())str += ".0";
	string intergral = str.substr(0, idx_dot); // intergral part of str
	string fractional = str.substr(idx_dot + 1, str.size() - idx_dot); // fractional part of str

	// ==== PROCESS INTERGRAL PART ====
	int nInt = (int)((intergral.size() % DIGITS == 0) ? (intergral.size() / DIGITS) : (intergral.size() / DIGITS) + 1); // calc range
	vector <int> _int(nInt);
	vector <bool> binInt;
	processIntergralPart(intergral,  _int, binInt);
	
	// ==== PROCESS FRACTIONAL PART ====
	int nFrac = (int)((fractional.size() % DIGITS == 0) ? (fractional.size() / DIGITS) : (fractional.size() / DIGITS) + 1); // calc range
	vector <int> _frac(nFrac);
	vector <bool> binFrac;
	processFractionalPart(fractional, _frac, binFrac, binInt);

	// ==== PROCESS EXPONENT ====
	int floating = 0;
	int exponent = 0;
	if (intergral == "0") { // check if 0.xxxx
		floating = checkUnderflow(binFrac);
		if (!floating) {
			cout << "Error: Underflow" << endl;
			return;
		}
	}
	else floating = binInt.size() - 1; // dot move to left
	exponent = (floating > (-pow(2, EXPONENT - 1) + 2))? floating + (pow(2, EXPONENT - 1) - 1) : 0;

	vector <int> ex;
	ex.push_back(exponent);

	for (int i = 15; i >= 1 && !isZero(ex); i--) {
		if (mod2(ex)) {
			x.data[0] = x.data[0] | (1 << (31-i));
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
	if (intergral == "0") {
		start = (floating > (-pow(2, EXPONENT - 1) + 2)) ? (-floating) : (-pow(2, EXPONENT - 1) + 2 - 1);
	}
	for (int i = start; (bit <= BITS) && (i < binFrac.size()); i++) {
		int idx = (int)(bit / 32); // index of x.data[]
		x.data[idx] = x.data[idx] | (binFrac[i] << (31 - (bit - 32 * idx)));
		bit++;
	}
}

void printBinaryQfloat(Qfloat x) {
	for (int i = 0; i < 128; i++) {
		int idx = (int)(i / 32);
		int bit = (x.data[idx] >> (31 - (i % 32))) & 1;
		cout << bit;
		if (i % 4 == 3) cout << "\t";
		if (i % 16 == 15) cout << "\n";
	}
}

Qfloat binToDecQFloat(bool *bit) {
	Qfloat x;

	for (int i = 0; i < BITS; i++) {
		int idx = (int)(i / 32);
		x.data[idx] = x.data[idx] | (bit[i] << (31 - (i - 32 * idx)));
	}
	return x;
}

bool *decToBin(Qfloat x) {
	bool *bit = new bool[BITS];

	for (int i = 0; i < BITS; i++) {
		int idx = (int)(i / 32);
		bit[i] = (x.data[idx] >> (31 - (i % 32))) & 1;
	}
	return bit;
}






void discreteDivideBy2(discrete &x) {

	// Fractional
	int r = mod2(x._frc);
	if (r == 1) x._frc.push_back(r * pow(10, DIGITS) / 2);

	// Integral
	r = mod2(x._int);
	x._frc[0] += r * pow(10, DIGITS) / 2;
}

void discreteMultiplyBy2(discrete &x) {

	// Fractional
	int R = multiply2(x._frc);
	
	// Integral
	int r = multiply2(x._int);
	if (r == 1) x._int.insert(x._int.begin(), 1);
	x._int[x._int.size() - 1] += R;

}

discrete discreteSum(discrete x, discrete y) {
	//print(y); cout << endl;
	discrete sum;
	int r = 0;

	// Fractional
	int dif = x._frc.size() - y._frc.size();
	for (int i = 0; i < abs(dif); i++) {
		sum._frc.insert(sum._frc.begin(), (dif > 0) ? x._frc[x._frc.size() - i - 1] : y._frc[y._frc.size() - i - 1]);
	}

	int size = (dif > 0) ? y._frc.size() : x._frc.size();
	int s = x._frc[size - 1] + y._frc[size - 1];
	r = s / pow(10, DIGITS);
	s -= r * pow(10, DIGITS);
	sum._frc.insert(sum._frc.begin(), s);
	
	for (int i = size - 2; i >= 0; i--) {
		int s = x._frc[i] + y._frc[i];
		s += r;
		r = s / pow(10, DIGITS);
		s -= r * pow(10, DIGITS);
		sum._frc.insert(sum._frc.begin(), s);
	}

	// Integral
	int xSize = x._int.size();
	int ySize = y._int.size();

	while (xSize > 0 && ySize > 0) {
		s = x._int[--xSize] + y._int[--ySize];
		s += r;
		r = s / pow(10, DIGITS);
		s -= r * pow(10, DIGITS);
		sum._int.insert(sum._int.begin(), s);
	}

	if (xSize > 0) {
		sum._int.insert(sum._int.begin(), x._int[--xSize] + r);

		while (xSize > 0) {
			sum._int.insert(sum._int.begin(), x._int[--xSize]);
		}
	}
	if (ySize > 0) {
		sum._int.insert(sum._int.begin(), y._int[--ySize] + r);

		while (ySize > 0) {
			sum._int.insert(sum._int.begin(), y._int[--ySize]);
		}
	}

	return sum;
}

void printQfloat(Qfloat x) {
	int bit;
	discrete _x;

	// calc EXPONENT
	int exponent = 0;
	for (int i = 15; i >= 0; i--) {
		bit = (x.data[0] >> (31 - i)) & 1;
		exponent += bit * pow(2, 15 - i);
	}
	exponent -= (pow(2, EXPONENT - 1) - 1);

	// initial
	if (exponent == -(pow(2, EXPONENT - 1) - 1)) {
		_x._int.push_back(0);
		exponent++;
	}
	else {
		_x._int.push_back(1);
	}
	_x._frc.push_back(0);
	discrete temp;
	temp._int.push_back(1);
	temp._frc.push_back(0);
	
	// find idx of the first bit 1
	int i = 16;
	bit = 0;
	while (!bit) {
		int idx = (int)(i / 32);
		bit = (x.data[idx] >> (31 - (i % 32))) & 1;
		i++;
	}

	if (i <= BITS) {
		for (int j = 0; j < i - 16; j++) {
			discreteDivideBy2(temp);
			/*cout << "divide" << endl;
			print(temp); getchar();*/
		}
		_x = discreteSum(_x, temp);
	}
	
	/*cout << "x" << endl;
	print(_x); getchar();*/

	// calc SIGNIFICAND
	while (i < BITS) {
		int idx = (int)(i / 32);
		bit = (x.data[idx] >> (31 - (i % 32))) & 1;
		discreteDivideBy2(temp);
		//print(temp); cout << endl;
		if (bit == 1) {
			//cout << "bit =" << i << endl;
			_x = discreteSum(_x, temp);
			/*cout << "sum" << endl;
			print(_x); getchar();*/
		}

		i++;
	}

	// processing
	cout << exponent << endl;
	for (int i = 0; i < abs(exponent); i++) {
		if (exponent >= 0) {
			discreteMultiplyBy2(_x);
			//print(_x); getchar();
		}
		else {
			discreteDivideBy2(_x);
			//print(_x); getchar();
		}
	}

	// convert to string
	string str = "";
	string _temp;
	bit = (x.data[0] >> 31) & 1;
	if (bit == 1) str += "-";
	for (int i = 0; i < _x._int.size(); i++) {
		_temp = to_string(_x._int[i]);
		if (i != 0)
			while (_temp.size() < DIGITS) _temp.insert(_temp.begin(), '0');
		str += _temp;
	}
	str += ".";

	while ((_x._frc[_x._frc.size() - 1] % 10 == 0) && (_x._frc[_x._frc.size() - 1] != 0))
		_x._frc[_x._frc.size() - 1] /= 10;

	for (int i = 0; i < _x._frc.size(); i++) {
		_temp = to_string(_x._frc[i]);
		if(i != _x._frc.size() - 1)
			while (_temp.size() < DIGITS) _temp.insert(_temp.begin(), '0');
		str += _temp;
	}

	cout << str << endl;
}

void print(discrete x) {
	for (int i = 0; i < x._int.size(); i++) {
		cout << x._int[i] << " ";
	}

	cout << " , ";
	for (int i = 0; i < x._frc.size(); i++) {
		cout << x._frc[i] << " ";
	}
}