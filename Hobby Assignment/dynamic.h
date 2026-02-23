#pragma once
#include<iostream>
#include<string>
using namespace std;

template<typename T>
class dynamic {
public:
	dynamic() : arr(nullptr), sized(0), capped(1)
	{
		arr = new T[capped];
		for (int i = 0; i < capped; ++i) {
			arr[i] = T();
		}
	}

	~dynamic() {
		delete[] arr;
		arr = nullptr;
		sized = 0;
		capped = 0;
	}

	int size() const {
		return sized;
	}

	int cap() const {
		return capped;
	}

	T getindex(int index) const {
		if (index < 0 || index >= sized) {
			return T();
		}
		return arr[index];
	}

	T operator[](int index) const {
		return getindex(index);
	}

	void push_back(const T& value) {
		if (sized >= capped) {
			resize(capped + 15);
		}
		arr[sized] = value;
		++sized;
	}

	bool removed(int index) {
		if (index < 0 || index >= sized) {
			return false;
		}
		for (int i = index; i < sized - 1; ++i) {
			arr[i] = arr[i + 1];
		}
		arr[sized - 1] = T();
		--sized;
		return true;
	}

	void clear() {
		for (int i = 0; i < sized; ++i) {
			arr[i] = T();
		}
		sized = 0;
	}

private:
	void resize(int newcap) {
		if (newcap <= capped) {
			return;
		}
		if (newcap < 1) {
			newcap = 1;
		}

		T* newarr = new T[newcap];
		for (int i = 0; i < newcap; ++i) {
			newarr[i] = T();
		}
		for (int i = 0; i < sized; ++i) {
			newarr[i] = arr[i];
		}

		delete[] arr;
		arr = newarr;
		capped = newcap;
	}

	T* arr;
	int sized;
	int capped;
};
