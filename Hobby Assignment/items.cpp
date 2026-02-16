#include "items.h"
#include <iostream>
#include <string>
using namespace std;

items::items():item_name(""), item_duration(0), item_rarity(COMMON), item_condition(FIELD_TESTED)
{
}
items::items(const string& name, int duration, rarity r, condition c): item_name(name), item_duration(duration), item_rarity(r), item_condition(c)
{
}

items::~items()
{

}


void items::setname(const string& name)
{
	item_name = name;
}
const string& items::getname() const
{
	return item_name;
}


void items::setduration(int duration)
{
	item_duration = duration;
}
int items::getduration() const
{
	return item_duration;
}


void items::setrarity(rarity r)
{
	item_rarity = r;
}
items::rarity items::getrarity() const
{
	return item_rarity;
}


void items::setcondition(condition c)
{
	item_condition = c;
}
items::condition items::getcondition() const
{
	return item_condition;
}


const char* items::raritystring(rarity r)
{
	if (r == COMMON)
		return "Common";
	else if (r == RARE)
		return "Rare";
	else if (r == EPIC)
		return "Epic";
	else if (r == LEGENDARY)
		return "Legendary";
	else
		return "Common";
}
const char* items::conditionstring(condition c)
{
	if (c == FACTORY_NEW)
		return "Factory New";
	else if (c == MINIMAL_WEAR)
		return "Minimal Wear";
	else if (c == FIELD_TESTED)
		return "Field Tested";
	else if (c == WELL_WORN)
		return "Well Worn";
	else if (c == BATTLE_SCARRED)
		return "Battle Scarred";
	else
		return "Field Tested";
}


void items::print() const
{
	cout << "Name: " << item_name << endl;
	cout << "Duration: " << item_duration << " Days" << endl;
	cout << "Rarity: " << raritystring(item_rarity) << endl;
	cout << "Condition: " << conditionstring(item_condition) << endl;
}
