#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
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
#include "itemmanager.h"
#include "dynamic.h"
#include "template.h"
#include "exceptionhandler.h"
#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#ifdef _DEBUG
struct CRTCtorLeakCheck
{
	CRTCtorLeakCheck()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
		_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
		_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
	}
};

static CRTCtorLeakCheck g_crtLeakCheck;
#endif


TEST_CASE("Equality operator == test")
{
	marketflags flags(true, false, true);
	itemdesc item1("Sword", 0, items::RARE, items::MINIMAL_WEAR, flags);
	itemdesc item2("Sword", 0, items::RARE, items::MINIMAL_WEAR, flags);
	CHECK(item1 == item2);
}

TEST_CASE("Equality operator == test for non equal")
{
	marketflags flags(true, false, true);

	itemdesc item1("Sword", 5, items::RARE, items::MINIMAL_WEAR, flags);
	item1.setfinalname("GUNS");

	itemdesc item2("Sword", 5, items::RARE, items::MINIMAL_WEAR, flags);
	item2.setfinalname("Rapier");

	CHECK((item1 == item2) == false);
}

TEST_CASE("operator << outputs one line sentances") {
	marketflags flags(true, false, true);
	itemdesc item1("Sword", 7, items::RARE, items::MINIMAL_WEAR, flags);
	stringstream ss;
	ss << item1;
	const string output = ss.str();
	CHECK(output.find("Name: Sword") != string::npos);
	CHECK(output.find("Duration: 7") != string::npos);
	CHECK(output.find("Rarity: Rare") != string::npos);
	CHECK(output.find("Condition: Minimal Wear") != string::npos);
}

TEST_CASE("operator << polymorphic test wiht pointers and references") {
	marketflags flags(true, false, true);
	items* ptr1 = new itemdesc("Sword", 7, items::RARE, items::MINIMAL_WEAR, flags);
	ostringstream ss;
	ss << *ptr1;
	const string output = ss.str();
	CHECK(output.find("Name: Sword") != string::npos);
	delete ptr1;
}

TEST_CASE("operator[] index returns correct inddex") {
	itemmanager manager;
	marketflags flags(true, false, true);
	manager += new itemdesc("Sword", 0, items::RARE, items::MINIMAL_WEAR, flags);
	manager += new itemgen("MSMC", 0, items::EPIC, items::FACTORY_NEW, 12, flags);
	CHECK(manager[0] != nullptr);
	CHECK(manager[1] != nullptr);
	CHECK(manager[0]->getname() == "Sword");
	CHECK(manager[1]->getname() == "MSMC");
}

TEST_CASE("operator [] invalid index throws") {
	itemmanager manager;
	CHECK_THROWS_AS(manager[0], exceptionhandler);
	CHECK_THROWS_AS(manager[-1], exceptionhandler);
}

TEST_CASE("operator += adds item increases size and stores pointer") {
	itemmanager manager;
	marketflags flags(true, false, true);

	CHECK(manager.getsize() == 0);

	items* p = new itemdesc("Sword", 0, items::RARE, items::MINIMAL_WEAR, flags);
	manager += p;

	CHECK(manager.getsize() == 1);
	CHECK(manager[0] == p);
	CHECK(manager[0]->getname() == "Sword");
}

TEST_CASE("operator -= removes indexes and shifts properly") {
	itemmanager	manager;
	marketflags flags(true, false, true);
	manager += new itemdesc("Sword", 0, items::RARE, items::MINIMAL_WEAR, flags);
	manager += new itemgen("MSMC", 0, items::EPIC, items::FACTORY_NEW, 12, flags);
	manager += new itemdesc("R8", 0, items::COMMON, items::WELL_WORN, flags);
	CHECK(manager.getsize() == 3);
	manager -= 1;
	CHECK(manager.getsize() == 2);
	CHECK(manager[0]->getname() == "Sword");
	CHECK(manager[1]->getname() == "R8");
	CHECK_THROWS_AS(manager[2], exceptionhandler);
}

TEST_CASE("operator -= invalid removal throws") {
	itemmanager manager;
	CHECK_THROWS_AS(manager -= 0, exceptionhandler);
	CHECK_THROWS_AS(manager -= -1, exceptionhandler);
}

TEST_CASE("template function test int") {
	CHECK(temptest<int>(5, 0, 10) == 5);
	CHECK(temptest<int>(-5, 0, 10) == 0);
}
TEST_CASE("template function test double") {
	CHECK(temptest<double>(5.5, 0.0, 10.0) == 5.5);
	CHECK(temptest<double>(-5.5, 0.0, 10.0) == 0.0);
}

TEST_CASE("class template stores and resizes") {
	dynamic<int> dyn;
	for (int i = 0; i < 20; ++i) {
		dyn.push_back(i);
	}
	CHECK(dyn.size() == 20);
	CHECK(dyn.getindex(0) == 0);
	CHECK(dyn.getindex(19) == 19);
}

TEST_CASE("class template invalid indexing throws") {
	dynamic<int> dyn;
	CHECK_THROWS_AS(dyn.getindex(0), exceptionhandler);
	CHECK_THROWS_AS(dyn[-1], exceptionhandler);
}

TEST_CASE("class template remove shifts") {
	dynamic<int> dyn;
	dyn.push_back(10);
	dyn.push_back(20);
	dyn.push_back(30);
	CHECK(dyn.removed(1) == true);
	CHECK(dyn.size() == 2);
	CHECK(dyn.getindex(0) == 10);	
	CHECK(dyn.getindex(1) == 30);
}

TEST_CASE("class template invalid removal throws") {
	dynamic<int> dyn;
	CHECK_THROWS_AS(dyn.removed(0), exceptionhandler);
	dyn.push_back(1);
	CHECK_THROWS_AS(dyn.removed(1), exceptionhandler);
}

TEST_CASE("itemmanager recursive test") {
	itemmanager manager;
	CHECK(manager.totalvalue() == doctest::Approx(0.0));

	marketflags flags(true, false, true);
	manager += new itemdesc("Sword", 0, items::RARE, items::MINIMAL_WEAR, flags);
	manager += new itemgen("MSMC", 0, items::EPIC, items::FACTORY_NEW, 12, flags);
	manager += new itemdesc("R8", 0, items::COMMON, items::WELL_WORN, flags);

	srand(123);
	const double expected = manager.totalvalue();

	srand(123);
	CHECK(manager.totalvalue() == doctest::Approx(expected));
}

TEST_CASE("itemmanager seq search empty returns -1") {
	itemmanager manager;
	CHECK(manager.seqsearch("Sword") == -1);
}

TEST_CASE("itemmanager sequential search finds correct index and if isnt found then returns -1") {
	itemmanager manager;
	marketflags flags(true, false, true);
	manager += new itemdesc("Sword", 0, items::RARE, items::MINIMAL_WEAR, flags);
	manager += new itemgen("MSMC", 0, items::EPIC, items::FACTORY_NEW, 12, flags);
	manager += new itemdesc("R8", 0, items::COMMON, items::WELL_WORN, flags);

	CHECK(manager.seqsearch("Sword") == 0);
	CHECK(manager.seqsearch("MSMC") == 1);
	CHECK(manager.seqsearch("Shield") == -1);
}

TEST_CASE("itemmanager bubble sort by name sorts properly") {
	itemmanager manager;
	marketflags flags(true, false, true);

	manager += new itemdesc("Zen", 0, items::RARE, items::MINIMAL_WEAR, flags);
	manager += new itemdesc("Aria", 0, items::RARE, items::MINIMAL_WEAR, flags);
	manager += new itemdesc("Dark", 0, items::EPIC, items::FACTORY_NEW, flags);

	manager.bubblesort();
	CHECK(manager[0]->getname() == "Aria");
	CHECK(manager[1]->getname() == "Dark");
	CHECK(manager[2]->getname() == "Zen");

}

TEST_CASE("itemmanager binary search returns correct index and if not found returns -1") {
	itemmanager manager;
	marketflags flags(true, false, true);
	manager += new itemdesc("Zen", 0, items::RARE, items::MINIMAL_WEAR, flags);
	manager += new itemdesc("Aria", 0, items::RARE, items::MINIMAL_WEAR, flags);
	manager += new itemdesc("Dark", 0, items::EPIC, items::FACTORY_NEW, flags);

	const int indxA = manager.binsearch("Aria");
	CHECK(indxA != -1);
	CHECK(manager[indxA]->getname() == "Aria");

	CHECK(manager.binsearch("Shield") == -1);
}

TEST_CASE("itemmanager empty binary search returns -1") {
	itemmanager manager;
	CHECK(manager.binsearch("Sword") == -1);
}