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
	item* inventory;	//dynamic array for inventory
	int inventory_size;
	int capacity;
	double maxvalue;
	raritysystem raritysys;
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
	void expandcap();

	//add item function
	void additem();
	
	//save report function
	void savereport();

	double calculateavg(const double* values, int size) const;
};

