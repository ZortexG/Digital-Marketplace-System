#pragma once
#include "items.h"
#include "marketflags.h"
#include <string>
class itemdesc: public items
{
public:
	itemdesc();
	itemdesc(const string&, int, rarity, condition, const marketflags&);

	void setfinalname(const string&);
	const string& getfinalname() const;

	void setmarketflags(const marketflags&);
	const marketflags& getmarketflags() const;

	void print() const;
private:
	string item_finalname;
	marketflags item_marketflags;
};

