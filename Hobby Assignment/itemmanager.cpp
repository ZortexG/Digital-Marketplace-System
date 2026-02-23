#include "itemmanager.h"
#include <iostream>
using namespace std;

itemmanager::itemmanager() : item_arr()
{
}

itemmanager::~itemmanager()
{
	clear();
}

int itemmanager::getsize() const
{
	return this->item_arr.size();
}

int itemmanager::getcapacity() const
{
	return item_arr.cap();
}


void itemmanager::add(items* ptr) {
	*this += ptr;
}

bool itemmanager::remove(int index) {
	const int oldsize = getsize();
	*this -= index;
	return getsize() != oldsize;
}
void itemmanager::clear() {
	for (int i=0;i<item_arr.size();i++) {
		delete item_arr[i];
	}
	item_arr.clear();
}

items* itemmanager::getind(int index) const {
	return item_arr.getindex(index);
}

items* itemmanager::operator[](int index) const {
	return getind(index);
}

itemmanager& itemmanager::operator+=(items* ptr) {
	if (!ptr) {
		return *this;
	}
	item_arr.push_back(ptr);
	return *this;
}

itemmanager& itemmanager::operator-=(int index) {
	items* vic = item_arr.getindex(index);
	if (!vic) {
		return *this;
	}
	delete vic;
	item_arr.removed(index);
	return *this;
}

void itemmanager::printall() const {
	for (int i = 0; i < item_arr.size(); ++i) {
		if (item_arr.getindex(i)) {
			cout << i << ". Item value is: " << item_arr.getindex(i)->getvalue() << endl;
			item_arr.getindex(i)->print();
		}
	}
}
