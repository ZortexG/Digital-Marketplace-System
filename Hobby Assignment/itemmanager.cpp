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
	return getsize();
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
	item_arr.clear(true);
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
	if (index < 0 || index >= getsize()) {
		throw exceptionhandler("Index out of bounds (itemmanager::operator-=)");
	}
	if (!item_arr.remove_at(index, true)) {
		throw exceptionhandler("Index out of bounds (itemmanager::operator-=)");
	}
	return *this;
}

void itemmanager::printall() const {
	int i = 0;

	for (itemslist::iterator it = item_arr.begin(); it.hascurrent(); it.next(), ++i) {
		if (it.data()) {
			cout << i << ". Item value: " << it.data()->getvalue() << endl;
			it.data()->print();
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
				itemslist::iterator it = item_arr.begin();
				for (int k = 0; k < i; ++k) it.next();
				items*& a = it.data();
				it.next();
				items*& b = it.data();

				items* tmp = a;
				a = b;
				b = tmp;

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

double itemmanager::totalvalue_rec(itemslist::iterator it) const
{
	if (!it.hascurrent()) {
		return 0.0;
	}

	items* cur = it.data();
	double current = 0.0;
	if (cur) {
		current = cur->getvalue();
	}
	else {
		current = 0.0;
	}

	it.next();
	return current + totalvalue_rec(it);
}