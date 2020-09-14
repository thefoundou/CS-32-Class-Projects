#include "Set.h"
#include <iostream>

using namespace std;



Set::Set()
	: m_size(0)
{
	m_head = new Node;									// Creates a dummy node associted with our head pointer /////////////////////////////////////////////////////////////////////////

//	m_head->m_val = "exist";	// Solely for testing purposes
	m_head->m_next = m_head;							// creates a circularly linked list (of zero elements)
	m_head->m_prev = m_head;
}

Set::Set(const Set& other)
	: m_size(0)
{
	m_head = new Node;									// Creates a dummy node associted with our head pointer ////////////////////////////////////////////////////////////////////////

//	m_head->m_val = "exist";	// Solely for testing purposes
	m_head->m_next = m_head;
	m_head->m_prev = m_head;
	
	Node* p = other.m_head->m_next;						///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (; p != other.m_head; p = p->m_next) {			// Iterates through the "example" linked list and creates nodes containing the same values (within the new list)
		insert(p->m_val);
		//cerr << "node inserted" << endl << endl;
	}
	//cerr << "All nodes created" << endl;
	p = nullptr;
	delete p;									// When p is deleted, this ensures it will not delete a node
}

Set& Set::operator=(const Set& other)
{
	if (m_head != other.m_head) {
	//	cerr << other.size() << endl;
		Set temp(other);										// Ensures that our two Sets do not have tangled pointers ////////////////////////////////////////////////////////////////////////
	//	cerr << temp.size() << endl;
		swap(temp);
		return *this;
	}
	//cerr << "You should get here" << endl;
	return *this;
}


Set::~Set()
{
	if (!empty()) {								// If the list is empty, the dummy node would have been attempted to be deleted twice
		Node* current = m_head->m_next;
		do {
			Node* temp = current;				// Sets up trailing pointer that is responsible for deleting nodes
			current = current->m_next;
			//cerr << temp->m_val << endl;
			delete temp;
		} while (current != m_head);			// do-while loop works with less complications that for loop
	}
	delete m_head;								// Delete dummy node once the rest of the list is deleted
}


bool Set::empty() const
{
	if (m_size == 0)
		return true;
	return false;
}

int Set::size() const
{
	return m_size;
}

bool Set::insert(const ItemType& value)
{
	Node* temp = m_head->m_next;
	while (temp != m_head)														// While loop to check if value already exists within loop
	{
		ItemType x = temp->m_val;
		if (x == value)
		{
			//cerr << "Node not double printed" << endl;
			return false;
		}
		temp = temp->m_next;
	}
	//cerr << "Check 1" << endl;
	Node* newNode = new Node(value,m_head->m_prev, m_head);						// Establish new node with desired value ///////////////////////////////////////////////////////////
	//cerr << "Check 2" << endl;
	if (empty()) {																// In the case that no nodes (besides dummy) exist in the list yet
		m_head->m_next = newNode;												// Links dummy to the list
	//	cerr << "Check 3a" << endl;
	}
	else {
		m_head->m_prev->m_next = newNode;										// Links the previous last node in the list to the new last node
	//	cerr << "Check 3b" << endl;
	}
	m_head->m_prev = newNode;													// Links the dummy node to the last node in the list
	//cerr << "Check 4" << endl;
	m_size++;
	//cerr << "Check 5" << endl;
	return true;
}

bool Set::erase(const ItemType& value)
{
	for (Node* p = m_head->m_next; p != m_head; p = p->m_next) {				// The value we are tryng to delete exists within the list
		if (p->m_val == value) {
			//cerr << "Pointer set to node to be erased" << endl << endl;
			Node* q = p->m_prev;
			//cerr << "node created" << endl;
			q->m_next = p->m_next;												// Sets previous node's m_next to the next node's address
			//cerr << "previous nodes next set to next node" << endl << endl;
			p->m_next->m_prev = q;												// Sets next node's m_prev to the previous node's address
			//cerr << p->m_val << endl;
			delete p;															// Deletes the node that holds the value we are looking to erase
			//cerr << "erased node successfully" << endl;
			m_size--;
			return true;
		}
	}
	return false;
}

bool Set::contains(const ItemType& value) const
{
	for (Node* p = m_head->m_next; p != m_head; p = p->m_next) {				// Iterates through until it finds a node containing the value that was inputted
		if (p->m_val == value) {
			return true;
		}
	}
	return false;																// returns false if not found
}

bool Set::get(int pos, ItemType& value) const
{
	if (pos >= size() || pos < 0) {												// ensure we are not going to exhibit undefined behavior
		return false;
	}
	for (Node* p = m_head->m_next; p != m_head; p = p->m_next) {				// This iterating pointer will be pointing to the node with the value that is greater than
		int count = 0;															// pos elements when found
		for (Node* q = m_head->m_next; q != m_head; q = q->m_next) {			// Iterate through the list (will give us a second node to compare to our first node)
			if (p->m_val > q->m_val) {											// Compares the values held in the two nodes
				count++;
			}
		}
		if (count == pos) {														// If the value in node is bigger than the proper amount of other values, set value to this value and return true
			value = p->m_val;
			return true;
		}
	}
	cerr << "You should not get here!" << endl;									// To ensure that you cannot fall off the bottom of the function and to see if something goes very wrong in out search
	return false;
}

void Set::swap(Set& other) 
{
	Node* Temp = m_head;														// Changes what address these pointers point to
	m_head = other.m_head;														// Keeps both linked lists intact just switches what we access each list with
	other.m_head = Temp;

	int b = m_size;																// swaps size of each one
	m_size = other.m_size;
	other.m_size = b;
}



// NON-MEMBER FUNCTIONS OF SET

void unite(const Set& s1, const Set& s2, Set& result)
{
	Set tempSet;																// Creates temp array (protect from aliasing)
	for (int i = 0; i < s1.size(); i++) {										// Fills temp with all elements of the first list
		ItemType x;
		s1.get(i, x);
		tempSet.insert(x);
	}
	for (int i = 0; i < s2.size(); i++) {										// Fills temp with all elements of list two that do not exist within list one
		ItemType y;
		s2.get(i, y);
		tempSet.insert(y);
	}
	result.swap(tempSet);														// swap set Temp with set value -- the new temp set is then deallocated 
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
	Set temp(s1);																// creates a copy of list one (protect from aliasing)
	//cerr << "copy constructore success" << endl;
	for (int i = 0; i < s1.size(); i++) {										// Iterate through temp and store each value	
		ItemType x;
		temp.get(i, x);
	//	cerr << "temp get success" << endl;
		for (int k = 0; k < s2.size(); k++) {									// For each value held from temp, iterate through list 2
			ItemType y;
			s2.get(k, y);														// Store the iterated values from second list
			//cerr << "s2 get success" << endl;
			if (x == y) {														// If the values are the same, delete this node from temp list
				temp.erase(y);
				i--;															// Ensure that we wont possibly skip over the next deletable value
			//	cerr << "erase success" << endl;
			}
		}
	}
	result = temp;
}