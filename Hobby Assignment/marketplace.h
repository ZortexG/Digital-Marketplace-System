//Backbone of the code, contains most of the functions
#pragma once
#include"items.h"
#include "pricingsystem.h"
#include "raritysystem.h"
#include "condtitionsystem.h"
#include "inputvalidator.h"

#include <string>
using namespace std;

class marketplace :public items
{
private:	//all required variables
	int inventory_size;
	item inventory[100];
	int capacity;
	double maxvalue;
	raritysystem raritysys; //helper functions
	condtitionsystem conditionsys;
	pricingsystem pricingsys;
	inputvalidator inputsys;
public:
	marketplace();
	~marketplace();
	//menu or visual functions
	void introbanner();
	void menu();
	void displayinventory();
	void extramenu();
	void tracksales();
	//void expandcap();

	//add item function
	void additem();

	//save report function
	void savereport();

	double calculateavg(const double*, int) const;

	int getinventorysize() const;
	//int getcapacity() const;
	int gettotalval() const;

	void additemtodirect(const item&); //
};

