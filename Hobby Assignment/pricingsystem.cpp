#include "pricingsystem.h"
#include <cstdlib>

double pricingsystem::pricegen(string rarity, string condition)
{
	double randprice = rand() % 26;	//Here is the pricing system. Right now I made it so that the pricing is random
	double baseprice = randprice * 2.5;	
	double raritymultiplier;
	double conditionmultiplier;
	if (rarity == "Common") {	//Though the pricing is random, it is influenced by the rarity and condition. The multipliers are as follows
		raritymultiplier = 1.0;
	}
	else if (rarity == "Rare") {
		raritymultiplier = 1.2;
	}
	else if (rarity == "Epic") {
		raritymultiplier = 1.5;
	}
	else if (rarity == "Legendary") {
		raritymultiplier = 2.0;
	}
	else {
		raritymultiplier = 1.0;
	}

	if (condition == "Battle-Scarred") {
		conditionmultiplier = 0.5;
	}
	else if (condition == "Well-Worn") {
		conditionmultiplier = 0.75;
	}
	else if (condition == "Field-Tested") {
		conditionmultiplier = 1.0;
	}
	else if (condition == "Minimal Wear") {
		conditionmultiplier = 1.25;
	}
	else if (condition == "Factory New") {
		conditionmultiplier = 1.5;
	}
	else {
		conditionmultiplier = 1.0;
	}
	return baseprice * raritymultiplier * conditionmultiplier; //formula to calculate the price
}
