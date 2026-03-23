#pragma once
#include "items.h"
#include"exceptionhandler.h"
#include<vector>
#include"dynamic.h"
#include<string>
using namespace std;
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

	double totalvalue() const;

	int seqsearch(const string&) const;
	void bubblesort();
	int binsearch(const string&);
private:
	vector<items*> item_arr;

	double totalvalue_rec(int) const;
};

