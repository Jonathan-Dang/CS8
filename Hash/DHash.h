#pragma once
#include "record.h"
#include "../Vector/Vector.h"
#include <iostream>
#include <cassert>
#include <iomanip>
using namespace std;

template <typename T>
class DHash
{
public:
	DHash<T>(unsigned int capacity = 811);

	void insert(const int key, const T value);
	void insert(const record<T>& r);
	void remove(const int key);	
	bool search(const int key, record<T>& found_record);

	unsigned int size() const { return _size; }
	unsigned int capacity() const { return _hash.capacity(); }
	unsigned int collision() { return _collision; }
	bool is_present(int key);
	bool empty();

	friend ostream& operator <<(ostream& outs, DHash<T>& print)
	{
		print.Print();
		return outs;
	}

private:
	Vector<record<T>> _hash;
	unsigned int _size;
	unsigned int _collision;

	static const int NEVER_USED = -1;
	static const int PREVIOUSLY_USED = -2;

	void Print();

	int hash1(int key);
	int hash2(int key);
	int next_index(int index, int key);
	bool find_index(int key, int& index);
	bool never_used(int index);
	bool vacantcy(int index);
	bool full();
};

template<typename T>
inline DHash<T>::DHash(unsigned int capacity) :_size(0), _collision(0)
{
	if (capacity > 811)
		capacity = 811;

	if (capacity % 2 != 0)
		capacity++;
	_hash.set_capacity(capacity / 2);

	for (int i = 0; i < capacity; i++)
	{
		_hash[i] = record<T>(NEVER_USED,T());
	}
}

template<typename T>
inline void DHash<T>::insert(const int key, const T value)
{
	insert(record<T>(key, value));
}

template<typename T>
inline void DHash<T>::insert(const record<T>& r)
{
	assert(r._key >= 0);

	if (full())
		return;

	int index;
	if (!find_index(r._key, index))
	{
		assert(size() < capacity());
		int temp = 0;
		index = hash1(r._key);
		while (!vacantcy(index) && temp < capacity())
		{
			index = next_index(index,r._key);
			temp++;
			_collision++;
		}
		if(temp < capacity())
			_size++;
	}

	_hash[index] = r;
	
}

template<typename T>
inline void DHash<T>::remove(const int key)
{
	int index;
	if (find_index(key, index))
	{
		_hash[index]._key = PREVIOUSLY_USED;
		_size--;
	}
}

template<typename T>
inline bool DHash<T>::search(const int key, record<T>& found_record)
{
	assert(key >= 0);

	int index;
	if (find_index(key, index))
	{
		found_record = _hash[index];
		return true;
	}
	return false;
}

template<typename T>
inline void DHash<T>::Print()
{
	for (int i = 0; i < capacity(); i++)
	{
		cout << "[" << setw(4) << setfill('0') << i << "] ";
		if (!vacantcy(i))
		{
			cout << "{" << setw(4) << setfill('0') << _hash[i]._key << "|" << setw(4)
				<< setfill('0') << _hash[i]._value << "}";
			if (hash1(_hash[i]._key) != i)
			{
				cout << "(" << setw(4) << setfill('0') << hash1(_hash[i]._key) << ") *";
			}
			cout << endl;
		}
		else
		{
			if (_hash[i]._key == PREVIOUSLY_USED)
				cout << "- - - - - - - - -" << endl;
			else
				cout << endl;
		}
	}
}

template<typename T>
inline int DHash<T>::hash1(int key)
{
	return key % capacity();
}

template<typename T>
inline int DHash<T>::hash2(int key)
{
	return 1 + (key % (capacity() - 2));
}

template<typename T>
inline int DHash<T>::next_index(int index, int key)
{
	return (index + hash2(key)) % capacity();
}

template<typename T>
inline bool DHash<T>::is_present(int key)
{
	int index = hash1(key);
	int index2 = hash2(key);
	if (_hash[index]._key == key)
		return true;
	else if (_hash[index2]._key == key)
		return true;
	else
		return false;
}

template<typename T>
inline bool DHash<T>::empty()
{
	return _size == 0;
}

template<typename T>
inline bool DHash<T>::find_index(int key, int& index)
{
	assert(key >= 0);

	for (int i = 0; i < capacity(); i++)
	{
		if (_hash[i]._key == key)
		{
			index = i;
			return true;
		}
	}

	index = PREVIOUSLY_USED;
	return false;
}

template<typename T>
inline bool DHash<T>::never_used(int index)
{
	return _hash[index]._key == NEVER_USED;
}

template<typename T>
inline bool DHash<T>::vacantcy(int index)
{
	return _hash[index]._key == NEVER_USED ||
		_hash[index]._key == PREVIOUSLY_USED;
}

template<typename T>
inline bool DHash<T>::full()
{
	return size() == capacity();
}
