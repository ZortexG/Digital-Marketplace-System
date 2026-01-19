//This class is for item properties and identification
#pragma once
#include "items.h"
#include <string>
using namespace std;
class items
{
public:
	enum rarity	//Rarity of the said items
	{
		COMMON,
		RARE,
		EPIC,
		LEGENDARY
	};
	enum condition { //conditions of the items, inspired by CS items
		FACTORY_NEW,
		MINIMAL_WEAR,
		FIELD_TESTED,
		WELL_WORN,
		BATTLE_SCARRED
	};
	struct item { //struct for item stats
		string name;
		rarity item_rarity;
		condition item_condition;
		string type;
		double price;
		int quantity;
		double item_float;
		
	};
};


