#include "itemdesc.h"
#include "pricingsystem.h"
#include <iostream>
#include <string>
using namespace std;
itemdesc::itemdesc(): items(), item_finalname(""), item_marketflags()
{
}
itemdesc::itemdesc(const string& name, int duration, rarity r, condition c, const marketflags& flags): items(name, duration, r, c), item_finalname(""), item_marketflags(flags)
{
}

void itemdesc::setfinalname(const string& finalname)
{
	item_finalname = finalname;
}
const string& itemdesc::getfinalname() const
{
	return item_finalname;
}

void itemdesc::setmarketflags(const marketflags& flags)
{
	item_marketflags = flags;
}
const marketflags& itemdesc::getmarketflags() const
{
	return item_marketflags;
}

double itemdesc::getvalue() const
{
	pricingsystem prices;
	string raritystr = items::raritystring(getrarity());
	string conditionstr = items::conditionstring(getcondition());
	return prices.pricegen(raritystr, conditionstr);
}

void itemdesc::print() const
{
	items::print();
	cout << "Item Name: " << item_finalname << endl;
	cout << "Base Name: " << getname() << endl;
	cout << "Duration: " << getduration() << " days" << endl;
	if (item_marketflags.istradable())
	{
		cout << "Tradable: Yes" << endl;
	}
	else
	{
		cout << "Tradable: No" << endl;
	}
	if (item_marketflags.ismarketable()) {
		cout << "Marketable: Yes" << endl;
	}
	else {
		cout << "Marketable: No" << endl;
	}
	if (item_marketflags.canbelisted()) {
		cout << "Listable: Yes" << endl;
	}
	else {
		cout << "Listable: No" << endl;
	}
}