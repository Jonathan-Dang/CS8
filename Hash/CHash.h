#pragma once
#include "record.h"
#include "../Vector/Vector.h"
#include "../AVL/AVL.h"
#include <iostream>
#include <cassert>
#include <string.h>
#include <iomanip>
using namespace std;

template <typename T>
class CHash
{
public:
	CHash<T>(unsigned int capacity = 811);

	void insert(const int key, const T value);
	void insert(const record<T>& r);
	void insert(const string& s);
	void remove(const int key);
	bool search(const int key, tree_node<record<T>>*& found_record);

	int size() const { return _size; }
	int capacity() const { return _h.capacity(); }
	int collision() const { return _collisions; }
	unsigned long stohash(const string& s);
	bool is_present(const int& key); //If has something, True
	bool empty() { return !size(); }
	void vectorized(Vector<record<T>>& v);

	friend ostream& operator <<(ostream& outs, CHash<T>& rhs)
	{
		rhs.Print();
		return outs;
	}	

private:
	Vector<AVL<record<T>>> _h;
	unsigned int _size;
	unsigned int _collisions;

	void Print();

	int hash(int key);
};

template<typename T>
inline CHash<T>::CHash(unsigned int capacity): _size(0), _collisions(0)
{
	if (capacity > 811)
		capacity = 811;

	if (capacity % 2 != 0)
		capacity++;

	_h.set_capacity(capacity / 2);
}

template<typename T>
inline void CHash<T>::insert(const int key, const T value)
{
	insert(record<T>(key, value));
}

template<typename T>
inline void CHash<T>::insert(const record<T>& r)
{
	assert(r._key >= 0);

	int index = hash(r._key);
	if (!_h[index].isEmpty())
		_collisions++;

	if (!is_present(r._key))
	{
		_h[index].insert(r);
		_size++;
	}
}

template<typename T>
inline void CHash<T>::insert(const string& s)
{
	unsigned long index = stohash(s);
	AVL<record<T>>& temp = _h[index];
	if (!temp.isEmpty())
		_collisions++;
	
	temp.insert(record<T>(index, s));
	_size++;
}

template<typename T>
inline void CHash<T>::remove(const int key)
{
	assert(key >= 0);
	int index = hash(key);
	if (_h[index].erase(record<T>(key)))
		_size--;
}

template<typename T>
inline bool CHash<T>::search(const int key, tree_node<record<T>>*& found_record)
{
	assert(key >= 0);
	int index = hash(key);
	tree_node<record<T>>* temp;
	if (_h[index].search(record<T>(key),temp))
	{
		found_record = temp;
		return true;
	}
	else
		return false;

}

template<typename T>
inline unsigned long CHash<T>::stohash(const string& s)
{
	unsigned long hash = 5381;
	int x;
	for (auto c : s)
	{
		x = c;
		hash = ((hash << 5) + hash) + x;
	}
	return hash % INTPTR_MAX;
}

template<typename T>
inline bool CHash<T>::is_present(const int& key)
{
	assert(key >= 0);
	int index = hash(key);
	AVL<record<T>> temp = _h[index];
	tree_node<record<T>>* throwaway;
	return temp.search(record<T>(key),throwaway);
}

template<typename T>
inline void CHash<T>::vectorized(Vector<record<T>>& v)
{
	Vector<record<T>> cool;
	for (int i = 0; i < capacity(); i++)
	{
		AVL<record<T>> tempAvl = _h[i];
		if (tempAvl.isEmpty())
		{
			Vector<record<T>> temp;
			tempAvl.vectorized(temp);
			for (int j = 0; j < temp.size(); j++)
			{
				cool.push_back(temp[j]);
			}
		}
	}
	v = cool;
}

template<typename T>
inline void CHash<T>::Print()
{
	for (int i = 0; i < capacity(); i++)
	{
		cout << "[" << setw(4) << setfill('0') << i << "] ";
		Vector<record<T>> temp;
		_h[i].vectorized(temp);
		for (int i = 0; i < temp.size(); i++)
		{
			cout << "{" << setw(4) << setfill('0') << temp[i]._key << "|"
				<< setw(4) << setfill('0') << temp[i]._value << "}->";
			if (i == temp.size() - 1)
				cout << "|||\n";
		}
		if (!_h[i].isEmpty())
			cout << endl;
	}
}

template<typename T>
inline int CHash<T>::hash(int key)
{
	return key % capacity();
}
