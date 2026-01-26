#include "pricingsystem.h"
#include <cstdlib>

double pricingsystem::pricegen(int rarityint, int condint)
{
	double randprice = rand() % 26;	//Here is the pricing system. Right now I made it so that the pricing is random
	double baseprice = randprice * 2.5;	
	double raritymultiplier;
	double conditionmultiplier;
	if (rarityint == 1) {	//Though the pricing is random, it is influenced by the rarity and condition. The multipliers are as follows
		raritymultiplier = 1.0;
	}
	else if (rarityint == 2) {
		raritymultiplier = 1.5;
	}
	else if (rarityint == 3) {
		raritymultiplier = 2.0;
	}
	else {
		raritymultiplier = 1.0;
	}

	if (condint == 1) {
		conditionmultiplier = 0.5;
	}
	else if (condint == 2) {
		conditionmultiplier = 0.75;
	}
	else if (condint == 3) {
		conditionmultiplier = 1.0;
	}
	else if (condint == 4) {
		conditionmultiplier = 1.25;
	}
	else if (condint == 5) {
		conditionmultiplier = 1.5;
	}
	else {
		conditionmultiplier = 1.0;
	}
	return baseprice * raritymultiplier * conditionmultiplier; //formula to calculate the price
}
