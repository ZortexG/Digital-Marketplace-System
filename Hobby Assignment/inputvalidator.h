//All input related functions and also validation functions (as it was mentioned in the requirements)

#pragma once
#include <string>
using namespace std;

class inputvalidator
{
public:
	string inputname(const string& prompt);
	double inputdouble(const string& prompt);
	int inputint(const string& prompt);

	bool validatestring(const string& input);
	bool validatedouble(double input);
	bool validateint(int input);
};

