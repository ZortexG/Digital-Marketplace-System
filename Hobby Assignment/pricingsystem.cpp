#include "pricingsystem.h"
#include <cstdlib>
#include <iostream>

// Constructor: Insert all rarity and condition multipliers into the maps.
// Using std::map here instead of hard-coded if-else chains because the map
// provides O(log n) lookup, keeps all values in one place, and is trivially
// extensible — adding a new rarity/condition requires only one new map entry.
pricingsystem::pricingsystem()
{
	// Insert: populate rarity multiplier map
	rarityMultipliers["Common"] = 1.0;
	rarityMultipliers["Rare"] = 1.2;
	rarityMultipliers["Epic"] = 1.5;
	rarityMultipliers["Legendary"] = 2.0;

	// Insert: populate condition multiplier map
	conditionMultipliers["Battle-Scarred"] = 0.5;
	conditionMultipliers["Well-Worn"] = 0.75;
	conditionMultipliers["Field-Tested"] = 1.0;
	conditionMultipliers["Minimal Wear"] = 1.25;
	conditionMultipliers["Factory New"] = 1.5;
}

double pricingsystem::pricegen(string rarity, string condition)
{
	double randprice = rand() % 26;	//Here is the pricing system. Right now I made it so that the pricing is random
	double baseprice = randprice * 2.5;

	// Lookup: use map::find to get multipliers instead of if-else chains
	double raritymultiplier = getRarityMultiplier(rarity);
	double conditionmultiplier = getConditionMultiplier(condition);

	return baseprice * raritymultiplier * conditionmultiplier; //formula to calculate the price
}

// Lookup: retrieve rarity multiplier by key; returns 1.0 if key does not exist
double pricingsystem::getRarityMultiplier(const string& rarity) const
{
	auto it = rarityMultipliers.find(rarity);
	if (it != rarityMultipliers.end())
		return it->second;
	return 1.0;
}

// Lookup: retrieve condition multiplier by key; returns 1.0 if key does not exist
double pricingsystem::getConditionMultiplier(const string& condition) const
{
	auto it = conditionMultipliers.find(condition);
	if (it != conditionMultipliers.end())
		return it->second;
	return 1.0;
}

// Delete: remove a rarity entry from the map (no-op if key does not exist)
void pricingsystem::removeRarity(const string& rarity)
{
	rarityMultipliers.erase(rarity);
}

// Delete: remove a condition entry from the map (no-op if key does not exist)
void pricingsystem::removeCondition(const string& condition)
{
	conditionMultipliers.erase(condition);
}

// Iterate: traverse and display all key-value pairs in both multiplier maps
void pricingsystem::printMultipliers() const
{
	cout << "Rarity Multipliers:" << endl;
	for (const auto& entry : rarityMultipliers)
	{
		cout << "  " << entry.first << ": x" << entry.second << endl;
	}
	cout << "Condition Multipliers:" << endl;
	for (const auto& entry : conditionMultipliers)
	{
		cout << "  " << entry.first << ": x" << entry.second << endl;
	}
}