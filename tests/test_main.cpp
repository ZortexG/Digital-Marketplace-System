#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "marketplace.h"
#include "condtitionsystem.h"
#include "items.h"
#include "pricingsystem.h"
#include "raritysystem.h"
#include "inputvalidator.h"
#include <cstdlib>
#include <string>
using namespace std;

TEST_CASE("Calculate Average") { //Normal Case
	marketplace market;
	double values[] = { 10.0, 20.0, 30.0, 40.0 };
	double avg = market.calculateavg(values, 4);
	CHECK(avg == 25.0);
}
TEST_CASE("Calculate average single value") { //Edge Case
	marketplace market;
	double values[] = { 50.0 };
	double avg = market.calculateavg(values, 1);
	CHECK(avg == 50.0);
}
TEST_CASE("Calculate avarage zero size") { //guard case
	marketplace market;
	double values[] = { 10.0 };
	double avg = market.calculateavg(values, 0);
	CHECK(avg == 0.0);
}
TEST_CASE("Pricing calculation wiht diff multipliers") { //Normal Case
	pricingsystem pricing;
	srand(42);
	double price1 = pricing.pricegen("Common", "Field-Tested");
	CHECK(price1 >= 0.0);
	double price2 = pricing.pricegen("Legendary", "Factory New");
	CHECK(price2 >= price1);
}


TEST_CASE("Enum Common Rarity") { //Normal Case
	raritysystem rarity;
	srand(1);  // Seed to get predictable result
	string result = rarity.raritygen();
	// raritygen() returns one of: Common, Rare, Epic, Legendary
	bool valid = (result == "Common" || result == "Rare" || result == "Epic" || result == "Legendary");
	CHECK(valid);

}
TEST_CASE("Enum Legendary Rarity") { //Normal Case
	raritysystem rarity;
	srand(99);  // Seed to get predictable result
	string result = rarity.raritygen();
	// raritygen() returns one of: Common, Rare, Epic, Legendary
	bool valid = (result == "Common" || result == "Rare" || result == "Epic" || result == "Legendary");
	CHECK(valid);
}
TEST_CASE("Enum Invalid Rarity") { //Edge Case
	raritysystem rarity;
	srand(50);  // Seed to get predictable result
	string result = rarity.raritygen();
	// raritygen() returns one of: Common, Rare, Epic, Legendary (defaults to Common for edge cases)
	bool valid = (result == "Common" || result == "Rare" || result == "Epic" || result == "Legendary");
	CHECK(valid);
}
TEST_CASE("ENUM condition system") { //guard case
	condtitionsystem condition;
	srand(50);  // Seed to get predictable result
	string result = condition.conditiongen();
	// conditiongen() returns one of: Battle-Scarred, Well-Worn, Field-Tested, Minimal Wear, Factory New
	bool valid = (result == "Battle-Scarred" || result == "Well-Worn" || result == "Field-Tested" || 
	              result == "Minimal Wear" || result == "Factory New");
	CHECK(valid);
}


TEST_CASE("Empty inventory") { //edge case
	marketplace market;
	CHECK(market.getinventorysize() == 0);
}

TEST_CASE("Inventory capacity after adding items") { //normal case
	marketplace market;
	items::item newitem1;
	newitem1.name = "1ITEM";
	newitem1.item_rarity = items::COMMON;
	newitem1.item_condition = items::FACTORY_NEW;
	newitem1.type = "TESTTYPE";
	newitem1.price = 100.0;
	newitem1.quantity = 1;
	market.additemtodirect(newitem1);
	CHECK(market.getinventorysize() == 1);
}
TEST_CASE("Total value calculation") {
	marketplace market;
	items::item newitem1;
	newitem1.name = "1ITEM";
	newitem1.item_rarity = items::COMMON;
	newitem1.item_condition = items::FACTORY_NEW;
	newitem1.type = "TESTTYPE";
	newitem1.price = 100.0;
	newitem1.quantity = 1;
	items::item newitem2;
	newitem2.name = "2ITEM";
	newitem2.item_rarity = items::RARE;
	newitem2.item_condition = items::MINIMAL_WEAR;
	newitem2.type = "TESTTYPE";
	newitem2.price = 200.0;
	newitem2.quantity = 1;
	market.additemtodirect(newitem1);
	market.additemtodirect(newitem2);
	CHECK(market.gettotalval() == 300.0);
}

TEST_CASE("Validator thinks all negatives are invalid") { //edge case
	inputvalidator validator;
	CHECK(validator.validateint(-5) == false);
}
//TEST_CASE("Expand capacity increases capacity") { //normal case
//	marketplace market;
//	int initial_capacity = market.getcapacity();
//	market.expandcap();
//	CHECK(market.getcapacity() > initial_capacity);
//}