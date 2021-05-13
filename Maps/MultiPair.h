#pragma once
#include <iostream>
#include <vector>
#include "../Btree/Btree Functions.h"
using namespace std;

template <typename K, typename E>
struct MultiPair
{
	K _key;
	vector<E> _MultiEntry;

	MultiPair() :_key(K()) {}
	MultiPair(K key) :_key(key) {}

	friend ostream& operator <<(ostream& outs, const MultiPair<K, E>& MP)
	{
		outs << "[" << MP._key << "|" << MP._MultiEntry << "]";
		return outs;
	}

	friend bool operator ==(const MultiPair<K, E>& lhs, const MultiPair<K, E>& rhs)
	{
		return lhs._key == rhs._key;
	}

	friend bool operator >(const MultiPair<K, E>& lhs, const MultiPair<K, E>& rhs)
	{
		return lhs._key > rhs._key;
	}

	friend bool operator <(const MultiPair<K, E>& lhs, const MultiPair<K, E>& rhs)
	{
		return lhs._key < rhs._key;
	}
};