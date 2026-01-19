//All input related functions and also validation functions(as it was mentioned in the requirements)
#include "inputvalidator.h"
#include <iostream>
#include <string>
using namespace std;

string inputvalidator::inputname(const string& prompt)
{
	string name;
	bool valid = false;
	while (!valid) {
		cout << prompt;
		cin >> ws;
		getline(cin, name);
		if (validatestring(name)) {
			valid = true;
		}
		else {
			cout << "Error, enter a valid name/string" << endl;
		}
	}
	return name;
}

double inputvalidator::inputdouble(const string& prompt)
{
	double val;
	bool valid = false;
	while (!valid) {
		cout << prompt;
		cin >> val;
		if (validatedouble(val)) {
			valid = true;
		}
		else {
			cout << "error, please enter a proper number (must be positive)" << endl;
		}
	}
	return val;
}

int inputvalidator::inputint(const string& prompt)
{
	int value;
	bool valid = false;
	while (!valid) {
		cout << prompt;
		cin >> value;
		if (validateint(value)) {
			valid = true;
		}
		else {
			cout << "Error, please enter a proper number (must be positive and whole number preferably)" << endl;
		}
	}
	return value;
}

bool inputvalidator::validatestring(const string& input)
{
	return !input.empty();
}
bool inputvalidator::validatedouble(double input)
{
	return input >= 0.0;
}
bool inputvalidator::validateint(int input)
{
	return input >= 0;
}
