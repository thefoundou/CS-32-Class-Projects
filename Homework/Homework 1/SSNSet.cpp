#include "SSNSet.h"
#include <iostream>

using namespace std;

SSNSet::SSNSet() {										// Create an empty SSN set.

	Set m_SSNset;

}

bool SSNSet::add(ItemType ssn) {

	return m_SSNset.insert(ssn);						//Insert function already does the work of returning true or false and adding

}
 
int SSNSet::size() const {								// Return the number of SSNs in the SSNSet.

	return m_SSNset.size();

}

void SSNSet::print() const {

	if (!m_SSNset.empty()) {							// Only allows function to run if m_SSNset is not empty

		Set printSSN;									// Creates temp set to copy set to

		for (int i = 0; i < size(); i++) {				// Copies our set into temp set
			ItemType b;
			m_SSNset.get(i, b);
			cout << b << endl;
		}
	}
}