#include "itemgen.h"
#include "pricingsystem.h"
#include <iostream>
#include <string>
using namespace std;
itemgen::itemgen(): items(), item_dropchance(0), item_flags()
{
}
itemgen::itemgen(const string& name, int duration, rarity r, condition c, int dropchance, const marketflags& flags): items(name, duration, r, c), item_dropchance(dropchance), item_flags(flags)
{
}

void itemgen::setdropchance(int dropchance)
{
	item_dropchance = dropchance;
}
int itemgen::getdropchance() const
{
	return item_dropchance;
}

void itemgen::setflags(const marketflags& flags)
{
	item_flags = flags;
}
const marketflags& itemgen::getflags() const
{
	return item_flags;
}

double itemgen::getvalue() const
{
	pricingsystem prices;
	string raritystr = items::raritystring(getrarity());
	string conditionstr = items::conditionstring(getcondition());
	return prices.pricegen(raritystr, conditionstr);
}

void itemgen::print() const {
	items::print();
	cout << "Drop chance: " << item_dropchance << "%" << endl;
	if (item_flags.istradable())
	{
		cout << "Tradable: Yes" << endl;
	}
	else
	{
		cout << "Tradable: No" << endl;
	}
	if (item_flags.ismarketable()) {
		cout << "Marketable: Yes" << endl;
	}
	else {
		cout << "Marketable: No" << endl;
	}
	if(item_flags.islimited()) {
		cout << "Limited: Yes" << endl;
	}
	else {
		cout << "Limited: No" << endl;
	}
	if (item_flags.canbelisted()) {
		cout << "Listable: Yes" << endl;
	}
	else {
		cout << "Listable: No" << endl;
	}
}