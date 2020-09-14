#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()	
{
	// TESTS FOR UNASSIGNED LONGS
	/*
	Set uls;
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) //Fills array competely
		uls.insert(i);
	assert(!uls.insert(12345678)); // Should fail to insert into full array
	assert(uls.erase(1)); // ensures that erasing works - reducing size
	assert(uls.insert(1)); // Tests that size was reduced and the array can intake another memeber
	for (int i = 0; i < DEFAULT_MAX_ITEMS; i++) //Fills array competely
		uls.erase(i);
	assert(uls.empty()); // ensures erase works across whole array... 
						 // even when numbers are "out of order"
	uls.erase({});
	cerr << "array size " << uls.size() << endl << endl; 
						 	   	// Test that erase cannot lower size less than zero
						 		// Trying to erase "empty space" should not be able to search
								// anywhere in with find() since size() = 0 so for loop shouldnt start
	assert(uls.insert(1));
	assert(uls.insert(3));
	assert(uls.insert(5));
	assert(uls.insert(4));
	assert(uls.insert(2));
	assert(uls.insert(6));
	cerr << "The following should be in order of least to greatest value in all cases" << endl;
	for (int i = 0; i < uls.size(); i++) {
		ItemType x;
		uls.get(i, x);
		cerr << x << endl; // If get() works correctly, order should be printed numerically
	}
	cerr << endl;
	assert(uls.contains(1));
	assert(uls.contains(3));
	assert(!uls.contains(7));
	
	int i = uls.size();
	ItemType x;
	assert(!uls.get(i + 1, x));

	Set aa;
	Set bb;

	bb.insert(1);
	bb.insert(2);
	bb.insert(3);
	bb.insert(4);
	bb.insert(5);

	assert(aa.size() == 0 && bb.size() == 5);
	aa.swap(bb);
	assert(aa.size() == 5 && bb.size() == 0);*/

	Set uls;

	assert(uls.insert("hello")); // Should fail to insert into full array
	assert(uls.erase("hello")); // ensures that erasing works - reducing size
	assert(uls.insert("hello")); // Tests that size was reduced and the array can intake another memeber
	assert(!uls.empty()); // ensures erase works across whole array... 
						 // even when numbers are "out of order"
	uls.erase({});
	cerr << "array size " << uls.size() << endl << endl;
	// Test that erase cannot lower size less than zero
	// Trying to erase "empty space" should not be able to search
	// anywhere in with find() since size() = 0 so for loop shouldnt start
	assert(uls.insert("a"));
	assert(uls.insert("b"));
	assert(uls.insert("c"));
	assert(uls.insert("d"));
	assert(uls.insert("e"));
	assert(uls.insert("f"));
	cerr << "The following should be in order of least to greatest value in all cases" << endl;
	for (int i = 0; i < uls.size(); i++) {
		ItemType x;
		uls.get(i, x);
		cerr << x << endl; // If get() works correctly, order should be printed numerically
	}
	cerr << endl;
	assert(uls.contains("a"));
	assert(uls.contains("e"));
	assert(!uls.contains("g"));

	int i = uls.size();
	ItemType x;
	assert(!uls.get(i + 1, x));

	Set aa;
	Set bb;

	bb.insert("a");
	bb.insert("b");
	bb.insert("c");
	bb.insert("d");
	bb.insert("e");

	assert(aa.size() == 0 && bb.size() == 5);
	aa.swap(bb);
	assert(aa.size() == 5 && bb.size() == 0);

}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}