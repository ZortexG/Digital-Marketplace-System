#include "doctest.h"
#include "marketplace.h"
#include "condtitionsystem.h"
#include "items.h"
#include "pricingsystem.h"
#include "raritysystem.h"
#include "inputvalidator.h"
#include "marketflags.h"
#include "itemdesc.h"
#include "itemgen.h"
#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

TEST_CASE("Base default constructor test")
{
	items item1;
	CHECK(item1.getname() == "");
	CHECK(item1.getduration() == 0);
	CHECK(item1.getrarity() == items::COMMON);
	CHECK(item1.getcondition() == items::FIELD_TESTED);
}

TEST_CASE("Base items added constructor test")
{
	items item1("Sword", 0, items::RARE, items::MINIMAL_WEAR);
	CHECK(item1.getname() == "Sword");
	CHECK(item1.getduration() == 0);
	CHECK(item1.getrarity() == items::RARE);
	CHECK(item1.getcondition() == items::MINIMAL_WEAR);
}

TEST_CASE("Markflags tester") {
	marketflags item1(true, true, false);
	CHECK(item1.istradable() == true);
	CHECK(item1.ismarketable() == true);
	CHECK(item1.islimited() == false);
	CHECK(item1.canbelisted() == true);

	marketflags item2(true, false, true); //helper function test
	CHECK(item2.canbelisted() == false);
}

TEST_CASE("Marketflags setters and getters test") {
	marketflags item1;
	item1.settradable(true);
	item1.setmarketable(false);
	item1.setlimited(true);

	CHECK(item1.istradable() == true);
	CHECK(item1.ismarketable() == false);
	CHECK(item1.islimited() == true);
	CHECK(item1.canbelisted() == false);
}

TEST_CASE("Itemdesc constructor sets base + derived + composition") {
	marketflags flags(true, false, true);
	itemdesc item1("Sword", 0, items::RARE, items::MINIMAL_WEAR, flags);
	item1.setfinalname("Excalibur");
	CHECK(item1.getname() == "Sword");
	CHECK(item1.getduration() == 0);
	CHECK(item1.getrarity() == items::RARE);
	CHECK(item1.getcondition() == items::MINIMAL_WEAR);
	CHECK(item1.getfinalname() == "Excalibur");
}

TEST_CASE("Itemgen constructor sets base + derived + composition") {
	marketflags flags(true, false, true);
	itemgen item1("Sword", 0, items::RARE, items::MINIMAL_WEAR, 50, flags);
	CHECK(item1.getname() == "Sword");
	CHECK(item1.getduration() == 0);
	CHECK(item1.getrarity() == items::RARE);
	CHECK(item1.getcondition() == items::MINIMAL_WEAR);
	CHECK(item1.getdropchance() == 50);
	CHECK(item1.getflags().istradable() == true);
	CHECK(item1.getflags().ismarketable() == false);
	CHECK(item1.getflags().islimited() == true);
	CHECK(item1.getflags().canbelisted() == false);
}