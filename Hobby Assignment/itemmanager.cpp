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
	return static_cast<int>(item_arr.size());
}

int itemmanager::getcapacity() const
{
	return static_cast<int>(item_arr.capacity());
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
	return item_arr.at(index);
}

items* itemmanager::operator[](int index) const {
	if(index < 0 || index >= getsize()) {
		throw exceptionhandler("Index out of bounds (itemmanager::operator[])");
	}
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
	if(index < 0 || index >= getsize()) {
		throw exceptionhandler("Index out of bounds (itemmanager::operator-=)");
	}
	delete item_arr.at(index);
	item_arr.erase(item_arr.begin() + index);
	return *this;
}

void itemmanager::printall() const {
	for (int i = 0; i < getsize(); ++i) {
		if (item_arr.at(i)) {
			cout << i << ". Item value: " << item_arr.at(i)->getvalue() << endl;
			item_arr.at(i)->print();
		}
	}
}

int itemmanager::seqsearch(const string& name) const {
	for (int i = 0; i < getsize(); ++i) {
		if(item_arr.at(i) && item_arr.at(i)->getname() == name) {
			return i;
		}
	}
	return -1;
}

void itemmanager::bubblesort() {
	const int n = getsize();
	if (n <= 1) {
		return;
	}
	for (int pass = 0; pass < n - 1; ++pass) {
		bool swapped = false;
		for (int i = 0; i < n - 1 - pass; ++i) {
			string left;
			if (item_arr.at(i)) {
				left = item_arr.at(i)->getname();
			}
			else {
				left = "";
			}
			string right;
			if (item_arr.at(i + 1)) {
				right = item_arr.at(i + 1)->getname();
			}
			else {
				right = "";
			}
			if (left > right) {
				items* tap = item_arr.at(i);
				item_arr.at(i) = item_arr.at(i + 1);
				item_arr.at(i + 1) = tap;
				swapped = true;
			}
		}
		if (!swapped) {
			break;
		}
	}
}

int itemmanager::binsearch(const string& name) {
	bubblesort();
	int low = 0;
	int high = getsize() - 1;
	while (low <= high) {
		const int mid = low + (high - low) / 2;
		string midname;
		if (item_arr.at(mid)) {
			midname = item_arr.at(mid)->getname();
		}
		else {
			midname = "";
		}
		if (midname == name) {
			return mid;
		}
		if (midname < name) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	return -1;
}

double itemmanager::totalvalue() const {
	return totalvalue_rec(0);
}

double itemmanager::totalvalue_rec(int index) const {
	if (index >= getsize()) {
		return 0.0;
	}
	items* it = item_arr.at(index);
	double current = 0;
	if (it) {
		current = it->getvalue();
	}
	return current + totalvalue_rec(index + 1);
}