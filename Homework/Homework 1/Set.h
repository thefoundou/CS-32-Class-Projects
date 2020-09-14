#ifndef SET_H
#define SET_H

#include <string>
//#include <iostream>

//using namespace std;

using ItemType = std::string;

//using ItemType = unsigned long;

const int DEFAULT_MAX_ITEMS = 240;

class Set
{
public:
	Set();

	bool empty() const;

	int size() const;

	bool insert(const ItemType& value);

	bool erase(const ItemType& value);

	bool contains(const ItemType& value) const;


	bool get(int i, ItemType& value) const;

	void swap(Set& other);

	void dump() const;

private:
	int m_size;
	ItemType m_a[DEFAULT_MAX_ITEMS];
	int find(const ItemType a[], const ItemType& value) const;
};

#endif // !SET_H