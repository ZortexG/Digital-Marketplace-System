//Backbone of the code, contains most of the functions
#include "marketplace.h"
#include"items.h"

#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include<cstdlib>
using namespace std;

marketplace::marketplace() //Base Values for the marketplace
{
	inventory_size = 0;
	maxvalue = 0.0;
	for (int i = 0; i < 100; ++i) {
		inventory[i] = {};
	}
}
marketplace::~marketplace()
{
}
void marketplace::introbanner() //Welcome intro banner
{
	cout << "Welcome to the digital marketplace!" << endl;

}

void marketplace::menu() //Menu
{
	int opt;
	do {
		cout << "Menu:" << endl;
		cout << "1. Display Inventory" << endl;
		cout << "2. Add Item" << endl;
		cout << "3. Save Report" << endl;
		cout << "4. Track Sales" << endl;
		cout << "5. Extra Functions" << endl;
		cout << "6. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> opt;
		switch (opt) {
		case 1:
			displayinventory();
			break;
		case 2:
			additem();
			break;
		case 3:
			savereport();
			break;
		case 4:
			tracksales();
			break;
		case 5:
			extramenu();
			break;
		case 6:
			break;
		default:
			cout << "Invalid option. Please try again." << endl;
			break;
		}
	} while (opt != 6);
}

void marketplace::extramenu() //Extra menu that can be expanded later
{
	int opt;
	do {
		cout << "Extra Functions Menu:" << endl;
		cout << "1. Calculate Average Price" << endl;
		cout << " 2. Return to main menu" << endl;
		cout << "Enter your choice: ";
		cin >> opt;
		switch (opt) {
		case 1:
			break;
		case 2:
			break;
		default:
			cout << "Invalid option. Please try again." << endl;
			break;
		}
	} while (opt != 2);
}

void marketplace::additem() {	//Adding new item function
	if (inventory_size >= 100) {
		cout << "Inventory is full. Cannot add more items." << endl;
		return;
	}
	item newitem;
	int opt;
	cout << "New Item: " << endl;
	newitem.name = inputsys.inputname("Enter the item's name: ");
	string r = raritysys.raritygen();
	if (r == "Common") {
		newitem.item_rarity = items::COMMON;
	}
	else if (r == "Rare") {
		newitem.item_rarity = items::RARE;
	}
	else if (r == "Epic") {
		newitem.item_rarity = items::EPIC;
	}
	else if (r == "Legendary") {
		newitem.item_rarity = items::LEGENDARY;
	}
	else {
		newitem.item_rarity = items::COMMON;
	}
	string c = conditionsys.conditiongen();
	if (c == "Factory New") {
		newitem.item_condition = items::FACTORY_NEW;
	}
	else if (c == "Minimal Wear") {
		newitem.item_condition = items::MINIMAL_WEAR;
	}
	else if (c == "Field-Tested") {
		newitem.item_condition = items::FIELD_TESTED;
	}
	else if (c == "Well-Worn") {
		newitem.item_condition = items::WELL_WORN;
	}
	else if (c == "Battle-Scarred") {
		newitem.item_condition = items::BATTLE_SCARRED;
	}
	else {
		newitem.item_condition = items::FIELD_TESTED;
	}
	newitem.type = inputsys.inputname("Enter the item's type: ");
	newitem.price = pricingsys.pricegen(r, c);
	inventory[inventory_size] = newitem;
	inventory_size++;
	cout << "Your item was added" << endl;
}

double marketplace::calculateavg(const double* values, int size) const //Calculating average price of items in inventory
{
	if (size <= 0) {
		return 0.0;
	}
	double total = 0.0;
	for (int i = 0; i < size; ++i) {
		total += values[i];
	}
	return total / size;
}

void marketplace::displayinventory() //Displaying the inventory with setw functions
{
	if (inventory_size == 0) {
		cout << "The inventory is empty" << endl;
		return;
	}
	cout << fixed << setprecision(2);
	cout << left << setw(20) << "Name" 
		<< setw(15) << "Rarity" 
		<< setw(20) << "Condition" 
		<< setw(15) << "Type" 
		<< setw(10) << "Price" << endl;
	for (int i = 0; i < inventory_size; ++i) {

        string raritystr;
		string conditionstr;

        if (inventory[i].item_rarity == items::COMMON) {
			raritystr = "Common";
        }
        else if (inventory[i].item_rarity == items::RARE) {
			raritystr = "Rare";
        }
        else if (inventory[i].item_rarity == items::EPIC) {
			raritystr = "Epic";
        }
        else if (inventory[i].item_rarity == items::LEGENDARY) {
			raritystr = "Legendary";
        }
        else {
			raritystr = "Unknown";
        }

        
        if (inventory[i].item_condition == items::FACTORY_NEW) {
			conditionstr = "Factory New";
        }
        else if (inventory[i].item_condition == items::MINIMAL_WEAR) {
			conditionstr = "Minimal Wear";
        }
        else if (inventory[i].item_condition == items::FIELD_TESTED) {
			conditionstr = "Field Tested";
        }
        else if (inventory[i].item_condition == items::WELL_WORN) {
			conditionstr = "Well Worn";
        }
        else if (inventory[i].item_condition == items::BATTLE_SCARRED) {
			conditionstr = "Battle Scarred";
        }
        else {
			conditionstr = "Unknown";
        }
		cout << left << setw(20) << inventory[i].name
			<< setw(15) << raritystr
			<< setw(20) << conditionstr
			<< setw(15) << inventory[i].type
			<< setw(10) << inventory[i].price << endl;
	}
}
void marketplace::tracksales() //tracking sales
{
	double totalvalue = 0.0;
	for (int i = 0; i < inventory_size; ++i) {
		totalvalue += inventory[i].price;
	}
	cout << fixed << setprecision(2);
	cout << "Total value of items in inventory: $" << totalvalue << endl;
}
void marketplace::savereport() { //Saving report to a text file
	if(inventory_size == 0) {
		cout << "The inventory is empty. No report to save." << endl;
		return;
	}
	ofstream reportfile("report.txt");
	if (!reportfile) {
		cout << "error creating the file." << endl;
		return;
	}
	reportfile << "Inventory Report" << endl;
	reportfile << fixed << setprecision(2);
	reportfile << left << setw(20) << "Name"
		<< setw(15) << "Rarity"
		<< setw(20) << "Condition"
		<< setw(15) << "Type"
		<< setw(10) << "Price" << endl;
	for (int i = 0; i < inventory_size; ++i) {
		string raritystr;
		string conditionstr;
		if (inventory[i].item_rarity == items::COMMON) {
			raritystr = "Common";
		}
		else if (inventory[i].item_rarity == items::RARE) {
			raritystr = "Rare";
		}
		else if (inventory[i].item_rarity == items::EPIC) {
			raritystr = "Epic";
		}
		else if (inventory[i].item_rarity == items::LEGENDARY) {
			raritystr = "Legendary";
		}
		else {
			raritystr = "Unknown";
		}
		
		if (inventory[i].item_condition == items::FACTORY_NEW) {
			conditionstr = "Factory New";
		}
		else if (inventory[i].item_condition == items::MINIMAL_WEAR) {
			conditionstr = "Minimal Wear";
		}
		else if (inventory[i].item_condition == items::FIELD_TESTED) {
			conditionstr = "Field Tested";
		}
		else if (inventory[i].item_condition == items::WELL_WORN) {
			conditionstr = "Well Worn";
		}
		else if (inventory[i].item_condition == items::BATTLE_SCARRED) {
			conditionstr = "Battle Scarred";
		}
		else {
			conditionstr = "Unknown";
		}
		reportfile << left << setw(20) << inventory[i].name
			<< setw(15) << raritystr
			<< setw(20) << conditionstr
			<< setw(15) << inventory[i].type
			<< setw(10) << inventory[i].price << endl;
	}
	reportfile << endl;
	reportfile.close();
	cout << "Report created successfully." << endl;
	cout << "Report saved to report.txt" << endl;
}

//Unit testing related functions

int marketplace::getinventorysize() const
{
	return inventory_size;
}

int marketplace::gettotalval() const
{
	double totalval = 0.0;
	for (int i = 0; i < inventory_size; ++i) {
		totalval += inventory[i].price;
	}
	return totalval;
}
void marketplace::additemtodirect(const item& newitem)
{
	if (inventory_size >= 100) {
		cout << "Inventory is full. Cannot add more items." << endl;
		return;
	}
	inventory[inventory_size] = newitem;
	inventory_size++;
}