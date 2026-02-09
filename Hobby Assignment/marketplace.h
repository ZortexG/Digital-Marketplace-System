//Backbone of the code, contains most of the functions
#pragma once
#include "items.h"
#include "pricingsystem.h"
#include "raritysystem.h"
#include "condtitionsystem.h"
#include "inputvalidator.h"

#include <string>
using namespace std;

class marketplace : public items
{
private:
	int inventory_size;
	items::item inventory[100];
	int capacity;
	double maxvalue;
	raritysystem raritysys;
	condtitionsystem conditionsys;
	pricingsystem pricingsys;
	inputvalidator inputsys;

public:
	marketplace();
	~marketplace();

	void introbanner();
	void menu();
	void displayinventory();
	void extramenu();
	void tracksales();

	void additem();
	void savereport();

	double calculateavg(const double*, int) const;

	int getinventorysize() const;
	int gettotalval() const;

	void additemtodirect(const items::item& newitem);
};




