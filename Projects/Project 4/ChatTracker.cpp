// ChatTracker.cpp

// This is a correct but inefficient implementation of
// the ChatTracker functionality.

#include "ChatTracker.h"
#include <string>
#include <list>
#include <vector>
#include <functional>
#include <iostream>
using namespace std;

// This class does the real work of the implementation.

struct Info
{
	Info(string u, string c) : user(u), chat(c), count(0) {};
	string user;
	string chat;
	int count;
};

// CHAT TRACKER CLASS DEF //

class ChatTrackerImpl
{
public:
	ChatTrackerImpl(int maxBuckets);
	void join(string user, string chat);
	int terminate(string chat);
	int contribute(string user);
	int leave(string user, string chat);
	int leave(string user);
	~ChatTrackerImpl();
private:
	vector<list<Info*>> m_ct;
	vector<list<Info*>> m_users;
	int m_maxBuckets = 0;
};



ChatTrackerImpl::ChatTrackerImpl(int maxBuckets)
{
	// Since this implementation does not use a hash table, we don't do
	// anything with the parameter and leave it unnamed so the compiler
	// doesn't issue a warning about an unused parameter.
	m_maxBuckets = maxBuckets;
	m_ct.resize(maxBuckets);      // = new HashTable(NUM_BUCK);
	m_users.resize(maxBuckets);					// = new UserHash(NUM_BUCK);

}

void ChatTrackerImpl::join(string user, string chat)
{
	int userBucket = hash<string>()(user) % m_maxBuckets; 
	list<Info*>::iterator iter = m_users[userBucket].begin();
	list<Info*>::iterator end = m_users[userBucket].end();

	while (iter != end) {
		if ((*iter)->user == user && (*iter)->chat == chat) {
			m_users[userBucket].push_front(*iter);
			iter = m_users[userBucket].erase(iter);
			return;
		}
		iter++;
	}

	int chatBucket = hash<string>()(chat) % m_maxBuckets;
	m_ct[chatBucket].push_front(new Info(user, chat));
	m_users[userBucket].push_front(m_ct[chatBucket].front());

}

int ChatTrackerImpl::terminate(string chat)
{
	int bucket = hash<string>()(chat) % m_maxBuckets; 
	int totContr = 0;
	list<Info*>::iterator iter = m_ct[bucket].begin();
	list<Info*>::iterator end = m_ct[bucket].end();


	while (iter != end) {
		if ((*iter)->chat == chat) {
			totContr += (*iter)->count;
			leave((*iter)->user, chat);
			delete (*iter);
			iter = m_ct[bucket].erase(iter);
		}
		else {
			iter++;
		}
	}

	return totContr;

}

int ChatTrackerImpl::contribute(string user)
{
	int userBucket = hash<string>()(user) % m_maxBuckets; 
	list<Info*>::iterator iter = m_users[userBucket].begin();
	list<Info*>::iterator end = m_users[userBucket].end();

	while (iter != end) {
		if ((*iter)->user == user) {
			(*iter)->count++;
			return (*iter)->count;
		}
		iter++;
	}	
	return 0;
}

int ChatTrackerImpl::leave(string user, string chat)
{
	int userBucket = hash<string>()(user) % m_maxBuckets; 
	int count = 0;
	list<Info*>::iterator iter = m_users[userBucket].begin();
	list<Info*>::iterator end = m_users[userBucket].end();

	while (iter != end) {
		if ((*iter)->user == user && (*iter)->chat == chat) {
			count = (*iter)->count;
			m_users[userBucket].erase(iter);
			return count;
		}
		iter++;
	}
	return -1;
}

int ChatTrackerImpl::leave(string user)
{
	int bucket = hash<string>()(user) % m_maxBuckets; 
	int count = 0;
	list<Info*>::iterator iter = m_users[bucket].begin();
	list<Info*>::iterator end = m_users[bucket].end();

	while (iter != end) {
		if ((*iter)->user == user) {
			count = (*iter)->count;
			m_users[bucket].erase(iter);
			return count;
		}
		iter++;
	}
	
	return -1;
}

ChatTrackerImpl::~ChatTrackerImpl() {
	

	for (int k = 0; k < m_ct.size();k++) {
		list<Info*>::iterator iter = m_ct[k].begin();
		while (iter != m_ct[k].end()) {
			delete* iter;
			iter = m_ct[k].erase(iter);
		}
	}
}


//*********** ChatTracker functions **************

// These functions simply delegate to ChatTrackerImpl's functions.
// You probably don't want to change any of this code.

ChatTracker::ChatTracker(int maxBuckets)
{
	m_impl = new ChatTrackerImpl(maxBuckets);
}

ChatTracker::~ChatTracker()
{
	delete m_impl;
}

void ChatTracker::join(string user, string chat)
{
	m_impl->join(user, chat);
}

int ChatTracker::terminate(string chat)
{
	return m_impl->terminate(chat);
}

int ChatTracker::contribute(string user)
{
	return m_impl->contribute(user);
}

int ChatTracker::leave(string user, string chat)
{
	return m_impl->leave(user, chat);
}

int ChatTracker::leave(string user)
{
	return m_impl->leave(user);
}

