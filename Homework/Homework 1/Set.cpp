#include "Set.h"
#include <iostream>

using namespace std;

Set::Set() 
	: m_size(0)
{
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) {							// Create an empty set (i.e., one with no items).
		m_a[i] = {};
	}
}

bool Set::empty() const {
	// Return true if the set is empty, otherwise false.
	if (size() == 0)
		return true;
	return false;
}

int Set::size() const {

	return m_size;
}

bool Set::insert(const ItemType& value) {

	if (find(m_a, value) != -1) {
		//	cerr << "item already in list" << endl;
		return false;
	}																	// Returns false if item is already in the set
	else if (m_size == DEFAULT_MAX_ITEMS) {
		//	cerr << "array is full" << endl;
		return false;
	}
	else																	// Inserts value into the first empty slot of the array
	{
		m_a[size()] = value;
		m_size++;
		return true;
	}
}

bool Set::erase(const ItemType& value) {

	int i = find(m_a, value);												// Finds position of value, returns -1 if not found

	if (i == -1)															// Returns false if item is not in the set
		return false;
	else																	// Deletes value from set by moving all terms after forward one space
	{
		for (; i < size()-1; i++) {
			m_a[i] = m_a[i + 1];
		}
		m_size--;
		return true;														// Important for if set is completely full when erase is called
	}
}

bool Set::contains(const ItemType& value) const {

	if (find(m_a, value) == -1)
		return false;
	return true;
}

bool Set::get(int i, ItemType& value) const {
	if (i < 0 || i >= size())												// Check if i is within the correct bounds of the "meaningful" array
		return false;

	int count[DEFAULT_MAX_ITEMS] = { 0 };

	for (int q = 0; q < size(); q++) {
		for (int k = 0; k < size(); k++) {
			if (m_a[q] > m_a[k]) {
				count[q]++;
			}
		}
	}

	for (int k = 0; k < size(); k++) {										// Put this whole thing in newSet
		if (count[k] == i) {
			value = m_a[k];
			return true;
		}
	}

	cerr << "You should not get here!" << endl;
	return false;
}

void Set::swap(Set& other) {

	ItemType a;
	int tempsize;

	for (int i = 0; i < DEFAULT_MAX_ITEMS - 1; i++) {						// Exchange the contents of this set with the other one.
		a = m_a[i];
		m_a[i] = other.m_a[i];
		other.m_a[i] = a;
	}

	tempsize = other.m_size;
	other.m_size = m_size;
	m_size = tempsize;
}

void Set::dump() const {

}

int Set::find(const ItemType a[], const ItemType& value) const {
	for (int i = 0; i < size(); i++) {
		if (a[i] == value)
			return i;
	}
	return -1;
}