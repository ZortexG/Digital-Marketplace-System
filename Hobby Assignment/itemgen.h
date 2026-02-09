#pragma once
#include"items.h"
#include"marketflags.h"
#include<string>
class itemgen :public items
{
public:
	itemgen();
	itemgen(const string&, int, rarity, condition, int, const marketflags&);

	void setdropchance(int);
	int getdropchance() const;

	void setflags(const marketflags&);
	const marketflags& getflags() const;

	void print() const;

private:
	int item_dropchance;
	marketflags item_flags;
};

