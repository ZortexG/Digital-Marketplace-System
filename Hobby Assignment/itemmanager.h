#pragma once
#include "items.h"
#include"dynamic.h"
class itemmanager
{
public:
	itemmanager();
	~itemmanager();

	int getsize() const;	
	int getcapacity() const;

	void add(items*);
	bool remove(int);
	void clear();

	items* getind(int) const;
	void printall() const;

	items* operator[](int) const;
	itemmanager& operator+=(items*);
	itemmanager& operator-=(int);
private:
	dynamic<items*> item_arr;
};

