#include "itemmanager.h"
#include <iostream>
using namespace std;

itemmanager::itemmanager(): item_arr(nullptr), size(0), capacity(0)
{
	if (capacity < 1) {
		capacity = 1;

	}
	item_arr = new items * [capacity];
	for(int i=0;i<capacity; i++)
	{
		item_arr[i] = nullptr;
	}
}

itemmanager::~itemmanager()
{
	clear();
	delete[] item_arr;
	item_arr = nullptr;
	capacity = 0;
}

int itemmanager::getsize() const
{
	return size;
}

int itemmanager::getcapacity() const
{
	return capacity;
}

void itemmanager::resize(int newsize) {
	if (newsize <= size) {
		newsize = size;

	}
	if (newsize < 1) {
		newsize = 1;
	}
	items** new_arr = new items * [newsize];
	for (int i = 0; i < size; i++) {
		new_arr[i] = item_arr[i];
	}
	delete[] item_arr;
	item_arr = new_arr;
	capacity = newsize;
}

void itemmanager::add(items* ptr) {
	if (!ptr) {
		return;
	}
	if(size >= capacity) {
		resize(capacity + 15);
	}
	item_arr[size] = ptr;
	++size;
}

bool itemmanager::remove(int index) {
	if(index < 0 || index >= size) {
		return false;
	}
	delete item_arr[index];
	for (int i = index; i < size - 1; i++) {
		item_arr[i] = item_arr[i + 1];
	}
	item_arr[size - 1] = nullptr;
	--size;
	return true;
}
void itemmanager::clear() {
	for (int i = 0; i < size; i++) {
		delete item_arr[i];
		item_arr[i] = nullptr;

	}
	size = 0;
}

items* itemmanager::getind(int index) const {
	if (index < 0 || index >= size) {
		return nullptr;
	}
	return item_arr[index];
}

void itemmanager::printall() const {
	for (int i = 0; i < size; i++) {
		if (item_arr[i]) {
			cout << i << ". item value: " << item_arr[i]->getvalue() << endl;
			item_arr[i]->print();
		}
	}
}

