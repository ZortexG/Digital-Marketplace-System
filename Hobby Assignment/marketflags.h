#pragma once
class marketflags
{
public:
	marketflags();
	marketflags(bool, bool, bool);

	void settradable(bool);
	bool istradable() const;

	void setmarketable(bool);
	bool ismarketable() const;

	void setlimited(bool);
	bool islimited() const;

	bool canbelisted() const;//helper

private:
	bool item_tradable;
	bool item_marketable;
	bool item_limited;
};

