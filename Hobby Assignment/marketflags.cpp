#include "marketflags.h"
#include <iostream>
#include <string>
using namespace std;
marketflags::marketflags(): item_tradable(true), item_marketable(true), item_limited(false)
{
}

marketflags::marketflags(bool tradable, bool marketable, bool limited): item_tradable(tradable), item_marketable(marketable), item_limited(limited)
{
}

void marketflags::settradable(bool tradable)
{
	item_tradable = tradable;
}
bool marketflags::istradable() const
{
	return item_tradable;
}

void marketflags::setmarketable(bool marketable)
{
	item_marketable = marketable;
}
bool marketflags::ismarketable() const
{
	return item_marketable;
}

void marketflags::setlimited(bool limited)
{
	item_limited = limited;
}
bool marketflags::islimited() const
{
	return item_limited;
}

bool marketflags::canbelisted() const {
	return item_tradable && item_marketable;
}