#ifndef SSNSET_H
#define SSNSET_H

#include "Set.h" //CHANGE BACK TO Set.h BEFORE TURN IN

class SSNSet
{
public:
	SSNSet();

	bool add(ItemType ssn);

	int size() const;

	void print() const;

private:
	Set m_SSNset;
};

#endif // !SSNSET_H