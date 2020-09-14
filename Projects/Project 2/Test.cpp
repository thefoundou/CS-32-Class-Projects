#include "Set.h"
#include <iostream>
#include <cassert>

using namespace std;

void check1() {									// Checks functions within single Set
												// Mainly focusing on size,empty,contains,get, and erase functions	
	Set ll;										// checks to see that all these implementations do not cause undefined behaviors
												
	assert(ll.empty());							// Tests emmpty function correctness
	assert(ll.size() == 0);						// Tests size on empty list
	assert(ll.insert("a"));
	assert(ll.contains("a"));					// Test contain
	assert(ll.size() == 1);
	assert(!ll.empty());						// Tests empty on non-empty function
	assert(ll.insert("b"));
	assert(ll.contains("b"));
	assert(ll.size() == 2);
	ItemType a;
	ItemType b;
	assert(ll.get(1, b) && b == "b");			// Tests get function ordering
	assert(ll.get(0, a) && a == "a");
	assert(ll.erase("a"));						// Makes sure erase works
	assert(!ll.contains("a"));
	assert(ll.get(0,b) && b == "b");			// Tests for correct get ordering when a node is deleted
	assert(ll.erase("b"));
	assert(!ll.erase("b"));						// Tests that erase correctly does nothing
	assert(!ll.contains("b"));
	assert(ll.insert("a"));
	assert(ll.insert("b"));
	assert(ll.insert("c"));
	assert(ll.insert("d"));
	assert(ll.insert("e"));
	assert(!ll.insert("a"));					// Will not double insert
	assert(!ll.insert("b"));
	assert(ll.size() == 5);
	assert(ll.get(0, b) && b == "a");			// Test get ordering again
	assert(ll.get(1, b) && b == "b");
	assert(ll.get(2, b) && b == "c");
	assert(ll.get(3, b) && b == "d");
	assert(ll.get(4, b) && b == "e");
	while(ll.size() > 0) {							// Checks if Iterating through all i's does not cause issues
		int i = ll.size() - 1;						// With node linking. That deleting nodes out of order will not cause issues
		ll.get(i, b);	
		ll.erase(b);}
	assert(ll.size() == 0);							// Test all nodes correctly deleted
	assert(ll.empty());								// Tests that deallocating an empty set does not cause problems
}

void check2() {										// Checks copy constructor, assignment operator, swap function
	Set ii; Set ll; Set jj;
	jj.swap(ll);
	assert(ll.insert("a"));
	assert(ll.insert("b"));
	assert(ll.insert("c"));
	assert(ll.insert("d"));
	assert(ll.insert("e"));
	jj.swap(ll);
	assert(jj.size() == 5);							// Tests for correct size after swapping
	assert(ll.size() == 0);
	assert(!jj.insert("a"));						// Test that front of list is properly search
	assert(!jj.insert("e"));						// Tests back of list to make sure it is properly searched
	ii = jj;
	assert(ii.size() == 5);							// Tests that assignment operator transfers size
	assert(ll.insert("a"));
	assert(ll.insert("b"));
	assert(ll.insert("c"));
	assert(ll.insert("d"));
	assert(ll.insert("e"));
	assert(ll.erase("a"));
	assert(ll.erase("b"));						// Erasing through all of the list to ensure linking
	assert(ll.erase("c"));						// and counting are not happening wrong
	assert(ll.erase("d"));
	assert(ll.erase("e"));
	assert(ll.empty());
	assert(!ii.empty());
	assert(!jj.empty());
	ii = jj = ll;								// Test that assignment operator works with multiple 				
	assert(ll.empty()							// Assignments in a single line
		&& ii.empty()
		&& jj.empty());
	assert(ll.insert("a"));
	assert(ll.insert("b"));
	assert(ll.insert("c"));
	assert(ll.insert("d"));
	assert(ll.insert("e"));
	jj.swap(ll);
	ii = ll = jj;								// Checks that ii,jj,ll are all destructed when containing nodes
}

void check3() {
	Set ii; Set ll; Set jj;
	assert(ll.insert("a"));					// These next 12 lines are to set up for unite and subtract testing
	assert(ll.insert("b"));
	assert(ll.insert("c"));
	assert(ll.insert("d"));
	assert(ll.insert("e"));
	assert(ll.size() == 5);
	assert(jj.insert("a"));
	assert(jj.insert("b"));
	assert(jj.insert("c"));
	assert(jj.size() == 3);
	assert(ii.insert("b"));
	assert(ii.insert("c"));
	assert(ii.size() == 2);
	unite(ii, jj, ii);
	assert(ii.size() == 3);
	subtract(ll, ii, ll);
	assert(ll.size() == 2);
	unite(ll, jj, ll);
	assert(ll.size() == 5);
	subtract(ii, ll, ii);					// Checks that count wont go negative and that the program will
	subtract(jj, ll, jj);					// Not attempt to erase what is not there
	assert(ii.empty()
		&& jj.empty());
	unite(ii, jj, ii);						// Test on empty sets
	assert(ii.empty());
	subtract(ii, jj, ii);					// Test on empty sets
	subtract(ii, ll, ii);
	assert(ii.size() == 0);
	subtract(ll, ii, ll);					// Subtract empty from non-empty
	subtract(ll, ii, jj);					// Tests returning to different set
	assert(ll.size() == 5
		&& jj.size() == 5);
}


int main()
{
	check1();

	check2();

	check3();

	cerr << "All test passed" << endl;
}