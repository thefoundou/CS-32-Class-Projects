/*#include "newSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Set s;
	assert(s.empty());
	ItemType x = 9876543;
	assert(!s.get(42, x) && x == 9876543); // x unchanged by get failure
	s.insert(123456789);
	assert(s.size() == 1);
	assert(s.get(0, x) && x == 123456789);

	Set a(1000);   // a can hold at most 1000 distinct items
	Set b(5);      // b can hold at most 5 distinct items
	Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
	ItemType v[6] = {3454645,23426746,8765325346,356434569,23456787,45678765};

		 
	cout << "size of a is " << a.size() << endl;
	cout << "size of b is " << b.size() << endl << endl;

	// No failures inserting 5 distinct items into b
	for (int k = 0; k < 5; k++)
		assert(b.insert(v[k]));

	// Failure if we try to insert a sixth distinct item into b
	//cout << "b ";
	assert(!b.insert(v[5]));
	//cout << "b insert fail (correct)" << endl;

	cout << "size of a is " << a.size() << endl;
	cout << "size of b is " << b.size() << endl << endl;

	// When two Sets' contents are swapped, their capacities are swapped
	// as well:
	a.swap(b);

	cout << "size of a is " << a.size() << endl;
	cout << "size of b is " << b.size() << endl << endl;

	//cout << "a ";
	assert(!a.insert(v[5]));
	//cout << "b ";
	assert(b.insert(v[5]));

	cout << "All Tests Passed" << endl;

} */


#include "newSet.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Set ss;
	assert(ss.insert("roti"));
	assert(ss.insert("pita"));
	assert(ss.size() == 2);
	assert(ss.contains("pita"));
	ItemType x = "laobing";
	assert(ss.get(0, x) && x == "pita");
	assert(ss.get(1, x) && x == "roti");
	ss.insert("1");
	ss.insert("2");
	ss.insert("3");
	ss.insert("4");
	ss.insert("5");


	for (int i = 0; i < ss.size(); i++) {				
		ItemType b;
		ss.get(i, b);
		cout << b << endl;
	}

	Set q(ss);

	Set w(15);
	w.insert("a");
	w.insert("b");
	w.insert("c");
	w.insert("d");
	w.insert("e");


	for (int i = 0; i < q.size(); i++) {	//This all is a check to see if copy constructor works
		ItemType b;
		q.get(i, b);
		cout << b << endl;
	}

	for (int i = 0; i < w.size(); i++) {	//This all is a check to see if copy constructor works
		ItemType b;
		w.get(i, b);
		cout << b << endl;
	}

	w = q;

	for (int i = 0; i < w.size(); i++) {	//This all is a check to see if copy constructor works
		ItemType b;
		w.get(i, b);
		cout << b << endl;
	}

}

int main()
{
	test();
	cout << "Passed all tests" << endl;


}

