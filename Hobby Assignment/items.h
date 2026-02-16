//This class is for item properties and identification
#pragma once
#include <string>

using namespace std;

class items
{

public:
	enum rarity	//Rarity of the said items
	{
		COMMON,
		RARE,
		EPIC,
		LEGENDARY
	};

	enum condition { //conditions of the items, inspired by CS items
		FACTORY_NEW,
		MINIMAL_WEAR,
		FIELD_TESTED,
		WELL_WORN,
		BATTLE_SCARRED
	};

	struct item
	{
		string name;
		rarity item_rarity;
		condition item_condition;
		string type;
		double price;
		int quantity;
		double item_float;

		item()
			: name(""),
			  item_rarity(COMMON),
			  item_condition(FIELD_TESTED),
			  type(""),
			  price(0.0),
			  quantity(0),
			  item_float(0.0)
		{
		}
	};

	items();
	items(const string&, int, rarity, condition);

	virtual ~items();

	void setname(const string&);
	const string& getname() const;

	void setduration(int);
	int getduration() const;

	void setrarity(rarity);
	rarity getrarity() const;

	void setcondition(condition);
	condition getcondition() const;

	virtual void print() const;

	virtual double getvalue() const = 0;


protected:
	string item_name;
	static const char* raritystring(rarity);
	static const char* conditionstring(condition);
private:
	int item_duration;
	rarity item_rarity;
	condition item_condition;
};


