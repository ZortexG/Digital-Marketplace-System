#include "marketplace.h"
#include "items.h"
#include "currencyapi.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;

#ifdef _DEBUG
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"	
#else

int main() {	//Main function, calling necessary functions and done :)
	
	runCurrencyAPI(); // Run the currency API demonstration
	marketplace market;
	market.introbanner();
	market.menu();
	return 0;
}

#endif