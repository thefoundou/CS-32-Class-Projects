#include "newSet.h"
#include <iostream>

using namespace std;

Set::Set() 
	: m_setMax(DEFAULT_MAX_ITEMS),
	m_size(0)
{
	m_a = new ItemType[m_setMax];

	for (int i = 0; i < m_setMax; i++) {							// Create an empty set (i.e., one with no items).
		m_a[i] = {};
	}
}

Set::Set(int numItems) 
	: m_setMax(numItems),
	m_size(0)
{
	if (m_setMax < 0) {
		cout << "The size of set must not be negative!" << endl;
		exit;
	}

	m_a = new ItemType[m_setMax];

	for (int i = 0; i < m_setMax; i++) {							// Create an empty set (i.e., one with no items).
		m_a[i] = {};
	}

	//cerr << "INITIALIZED WITHOUT ERRORS" << endl;
}

Set::Set(const Set& other)
	: m_size(other.m_size), 
	m_setMax(other.m_setMax)
{
	m_a = new ItemType[m_setMax]; 

	for (int i = 0; i < m_size; i++) {							// Create an empty set (i.e., one with no items).
		m_a[i] = other.m_a[i];
	}
}

Set::~Set()
{
	delete[] m_a;
}

Set& Set::operator=(const Set& rhs) {
	if (this != &rhs) {
		Set temp(rhs);
		swap(temp);
	}
	return *this;
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
	else if (m_size == m_setMax) {
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
		for (; i < size() - 1; i++) {
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
	
	int* count = new int [size()];

	for (int q = 0; q < size(); q++) {
		count[q] = 0;
	}


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
			delete[] count;
			return true;
		}
	}

	//Should not need to use this delete, stops memory leak in case code gets to this point (IT SHOUDLNT)
	delete[] count;
	cerr << "You should not get here!" << endl;
	return false;
}

void Set::swap(Set& other) {

	int tempsize;
	int tempMaxSize;

	ItemType *a = other.m_a;												// Exchange the contents of this set with the other one.								
	other.m_a = m_a;
	m_a = a;

	tempMaxSize = other.m_setMax;
	other.m_setMax = m_setMax;
	m_setMax = tempMaxSize;

	tempsize = other.m_size;
	other.m_size = m_size;
	m_size = tempsize;

	/*cout << "max size of a is " << m_setMax << endl;
	cout << "max size of b is " << other.m_setMax << endl;*/
}


int Set::find(const ItemType *a, const ItemType& value) const {
	for (int i = 0; i < size(); i++) {
		if (a[i] == value)
			return i;
	}
	return -1;
}