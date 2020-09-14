#ifndef NEWSET_H
#define NEWSET_H

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

	Set(int numItems);

	Set(const Set& other);

	~Set();

	Set& operator=(const Set& n);

	bool empty() const;

	int size() const;

	bool insert(const ItemType& value);

	bool erase(const ItemType& value);

	bool contains(const ItemType& value) const;


	bool get(int i, ItemType& value) const;

	void swap(Set& other);

private:
	int m_setMax;
	int m_size;
	ItemType * m_a;
	int find(const ItemType *a, const ItemType& value) const;
};

#endif // !SET_H#pragma once
