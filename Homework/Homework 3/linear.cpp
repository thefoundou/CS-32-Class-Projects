/*#include <iostream>
#include <string>
using namespace std;


bool somePredicate(string s)
{
	
	if (s.size() == 3) {
		//cout << "Some Predicate is true" << endl;
		return true;
	}
	else {
		//cout << "Some Predicate is false" << endl;
		return false;
	}
}*/

bool allFalse(const string a[], int n)
{
	if (n >= 2) {
		if (!allFalse(a, 1) || allFalse(a + 1, n - 1))
			return false;
	}

	if (n == 1) { 
		if (somePredicate(a[0])) {
			//cout << "Predicate is True" << endl;
			return false;
		}
	}
	if (n <= 0) {
		return true;
	}

	return true;
}

int countFalse(const string a[], int n)
{

	int count = 0;

	if (n >= 2) {
		count += countFalse(a, 1);
		count += countFalse(a + 1, n - 1);
	}

	if (n == 1) {
		if (!somePredicate(a[0])) {
			//cout << "Predicate is True" << endl;
			count++;
		}
	}
	if (n <= 0) {
		return 0;
	}

	return count;
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const string a[], int n)			// DOES NOT RETURN -1 WHEN NO ARGUMENTS ARE FALSE
{
	if (n <= 0) return -1;
	if (somePredicate(a[n - 1]))
		return firstFalse(a, n - 1);
	else if (firstFalse(a, n - 1) == -1)
		return n - 1;
	else
		return (firstFalse(a, n - 1));
}

int locateMaximum(const string a[], int n)
{
	if (n <= 0)
		return -1;

	int pos = 0;

	if (n == 1)
		return 0;

	if (n == 2) {
		if (a[0] >= a[1])
			return pos;
		else {
			pos++;
			return pos;
		}
	}

	if (n > 2) {
		int i = pos;
		i =+ (1 + locateMaximum(a + 1, n - 1));

		if (a[pos] >= a[i]) {
			return pos;
		}
		else
			return i;
	}

	// Should not get here
	return 0;
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not contain
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool contains(const string a1[], int n1, const string a2[], int n2)
{
	if (n2 <= 0)
		return true;
	if (n1 == 0 && n2 != 0)
		return false;

	if (a1[0] != a2[0]) {
		bool b = contains(a1 + 1, n1 - 1, a2, n2);
		if (b)
			return true;
	}

	if (a1[0] == a2[0]) {
		bool b = contains(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
		if (b)
			return true;
	}

	// Should not get here
	return false;
}

/*int main()
{
	//string a1[7] = {  "kyle", "a", "kenny", "b","butters" };
	//string a2[4] = { "kyle", "a", "kenny", "butters" };
	
	string a[7] = { "ajh","ndn","dcd", "sds","wdw","www","hhj" };

	bool b = allFalse(a, 5);

	if (b)
		cout << "woo" << endl;
	else 
		cout << "boo" << endl;

	int b = countFalse(a, 7);
	cout << b << endl;

}*/









