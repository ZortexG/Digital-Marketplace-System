#pragma once
#include "items.h"
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

private:
	void resize(int);
	items** item_arr;
	int size;
	int capacity;
};

