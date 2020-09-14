#ifndef SET_H
#define SET_H
#include <string>

using ItemType = std::string;
//using ItemType = unsigned long;
class Set
{
public:
	Set();
	Set(const Set& other);
	Set& operator=(const Set& other);
	~Set();
	bool empty() const;
	int size() const;
	bool insert(const ItemType& value);
	bool erase(const ItemType& value);
	bool contains(const ItemType& value) const;
	bool get(int pos, ItemType& value) const;
	void swap(Set& other);
private:
	struct Node {
		Node(const ItemType& value, Node* prev, Node* next)
			: m_val(value), m_prev(prev), m_next(next) {}
		Node()
			: m_val(), m_prev(nullptr), m_next(nullptr) {};
		ItemType m_val;
		Node* m_prev;
		Node* m_next;
	};
	int m_size;
	Node* m_head;
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set& s2, Set& result);

#endif // SET_H!