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
//(a)
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
	double price1 = pricing.pricegen(1, 1);
	CHECK(price1 >= 0.0);
	double price2 = pricing.pricegen(3, 5);
	CHECK(price2 >= price1);
}

//(b)
TEST_CASE("Enum Common Rarity") { //Normal Case
	raritysystem rarity;
	string result = rarity.raritysel(1);
	CHECK(result == "Common");

}
TEST_CASE("Enum Legendary Rarity") { //Normal Case
	raritysystem rarity;
	string result = rarity.raritysel(4);
	CHECK(result == "Legendary");
}
TEST_CASE("Enum Invalid Rarity") { //Edge Case
	raritysystem rarity;
	string result = rarity.raritysel(5);
	CHECK(result == "Common");
}
TEST_CASE("ENUM condition system") { //guard case
	condtitionsystem condition;
	string result = condition.conditionsel(3);
	CHECK(result == "Field Tested");
}

//(c)
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
//(d)
TEST_CASE("Validator accepts positive integer") { // normal case 
	inputvalidator validator; 
	CHECK(validator.validateint(10) == true); 
}

TEST_CASE("Validator thinks all negatives are invalid") { //edge case
	inputvalidator validator;
	CHECK(validator.validateint(-5) == false);
}

TEST_CASE("Price prediction with different rarity and condition") { //normal case
	pricingsystem pricing;
	srand(1);
	double price1 = pricing.pricegen(2, 3);
	CHECK(price1 >= 0.0);
}
