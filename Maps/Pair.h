#pragma once
#include <iostream>
using namespace std;

template <typename K,typename E>
struct Pair
{
	K _key;
	E _entry;

	Pair<K, E>() : _key(K()), _entry(E()) {}
	Pair<K,E>(K key, E entry) :_key(key), _entry(entry) {}

	friend ostream& operator <<(ostream& outs, const Pair& p)
	{
		outs << "[" << p._key << ":" << p._entry << "]";
		return outs;
	}

	friend bool operator ==(const Pair& lhs, const Pair& rhs)
	{
		return lhs._key == rhs._key;
	}
	friend bool operator >(const Pair& lhs, const Pair& rhs)
	{
		return lhs._key > rhs._key;
	}
	friend bool operator <(const Pair& lhs, const Pair& rhs)
	{
		return lhs._key < rhs._key;
	}
};

