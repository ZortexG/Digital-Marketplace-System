//Pricing system for the items

#pragma once
#include <string>
#include <map>
using namespace std;
class pricingsystem
{
public:
	pricingsystem();

	double pricegen(string, string);

	// Lookup: retrieve a multiplier by key from the maps (returns 1.0 if key not found)
	double getRarityMultiplier(const string&) const;
	double getConditionMultiplier(const string&) const;

	// Delete: remove a key-value pair from the maps
	void removeRarity(const string&);
	void removeCondition(const string&);

	// Iterate: traverse and display all key-value pairs in both maps
	void printMultipliers() const;

private:
	// std::map chosen over if-else chains: O(log n) lookup, easily extensible,
	// and adding a new rarity/condition only requires one map entry — no control flow changes.
	map<string, double> rarityMultipliers;
	map<string, double> conditionMultipliers;
};

