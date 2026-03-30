#include "itemslist.h"
#include "items.h"
#include <iostream>
using namespace std;

itemslist::node::node(items* d, node* n): data(d), next(n)
{
}

itemslist::iterator::iterator(node* start): current(start)
{
}

bool itemslist::iterator::hascurrent() const
{
	return current != nullptr;
}

void itemslist::iterator::next()
{
	if (current) {
		current = current->next;
	}
}

items*& itemslist::iterator::data() const
{
	if (!current) {
		throw exceptionhandler("iterator out of bounds (itemslist::iterator::data)");
	}
	return current->data;
}

itemslist::itemslist(): head(nullptr), tail(nullptr), sized(0)
{
}

itemslist::~itemslist()
{
	clear(false);
}

int itemslist::size() const
{
	return sized;
}

itemslist::iterator itemslist::begin() const
{
	return iterator(head);
}

void itemslist::push_front(items* ptr)
{
	if (!ptr) {
		return;
	}

	node* n = new node(ptr, head);
	head = n;

	if (!tail) {
		tail = head;
	}

	++sized;
}

void itemslist::push_back(items* ptr)
{
	if (!ptr) {
		return;
	}

	node* n = new node(ptr);

	if (!head) {
		head = tail = n;
	}
	else {
		tail->next = n;
		tail = n;
	}

	++sized;
}

items* itemslist::at(int index) const
{
	if (index < 0 || index >= sized) {
		throw exceptionhandler("Index out of bounds (itemslist::at)");
	}

	node* cur = head;
	for (int i = 0; i < index; ++i) {
		cur = cur->next;
	}

	return cur->data;
}

int itemslist::index_of_name(const string& name) const
{
	int i = 0;
	for (iterator it = begin(); it.hascurrent(); it.next(), ++i) {
		if (it.data() && it.data()->getname() == name) {
			return i;
		}
	}
	return -1;
}

bool itemslist::remove_at(int index, bool deleteItem)
{
	if (index < 0 || index >= sized) {
		return false;
	}

	node* prev = nullptr;
	node* cur = head;

	for (int i = 0; i < index; ++i) {
		prev = cur;
		cur = cur->next;
	}

	if (prev) {
		prev->next = cur->next;
	}
	else {
		head = cur->next;
	}

	if (cur == tail) {
		tail = prev;
	}

	if (deleteItem && cur->data) {
		delete cur->data;
		cur->data = nullptr;
	}

	delete cur;
	--sized;

	if (sized == 0) {
		head = tail = nullptr;
	}

	return true;
}

void itemslist::clear(bool deleteItems)
{
	while (head) {
		node* next = head->next;

		if (deleteItems && head->data) {
			delete head->data;
			head->data = nullptr;
		}

		delete head;
		head = next;
	}

	tail = nullptr;
	sized = 0;
}