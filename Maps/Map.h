#pragma once
#include "Pair.h"
#include "../Btree/BTree.h"
#include <iostream>
using namespace std;

template <typename K, typename E>
class Map
{
public:
	Map();

	void insert(const K& key, const E& entry = E());
	void remove(const K& key);

	E& operator[](const K& key);
	const E& operator[](const K& key) const;

	bool empty();
	bool contains(const K& key);
	void clear();
private:
	BTree<Pair<K, E>> _map;
};

template<typename K, typename E>
inline Map<K, E>::Map()
{
	//Left Blank Intentionally
}

template<typename K, typename E>
inline void Map<K, E>::insert(const K& key, const E& entry)
{
	_map.insert(Pair<K, E>(key, entry));
}

template<typename K, typename E>
inline void Map<K, E>::remove(const K& key)
{
	_map.remove(Pair<K, E>(key, E()));
}

template<typename K, typename E>
inline E& Map<K, E>::operator[](const K& key)
{
	return _map.get(Pair<K, E>(key, E()))._entry;
}

template<typename K, typename E>
inline const E& Map<K, E>::operator[](const K& key) const
{
	return _map.get(Pair<K, E>(key, E()))._entry;
}

template<typename K, typename E>
inline bool Map<K, E>::empty()
{
	return _map.empty();
}

template<typename K, typename E>
inline bool Map<K, E>::contains(const K& key)
{
	return _map.contains(Pair<K, E>(key, E()));
}

template<typename K, typename E>
inline void Map<K, E>::clear()
{
	_map.clear_tree();
}
