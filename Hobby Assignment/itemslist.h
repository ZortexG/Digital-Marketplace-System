#pragma once
#include <string>
#include "exceptionhandler.h"
using namespace std;
class items;

class itemslist
{
private:
	struct node
	{
		items* data;
		node* next;

		node(items*, node* = nullptr);
	};

public:
	class iterator
	{
	public:
		iterator(node* = nullptr);
		bool hascurrent() const;
		void next();

		items*& data() const;

	private:
		node* current;
	};

	itemslist();
	~itemslist();

	int size() const;
	iterator begin() const;

	void push_back(items*);
	void push_front(items*);

	items* at(int) const;


	int index_of_name(const string&) const;

	bool remove_at(int, bool);

	void clear(bool);

private:
	node* head;
	node* tail;
	int sized;
};

