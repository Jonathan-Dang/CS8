#pragma once
#include "../Btree/BTree.h"
#include "MultiPair.h"

template <typename K,typename E>
class MultiMap
{
public:
	MultiMap();

	void insert(const K& key);
	void remove(const K& key);

	vector<E>& operator[](const K& key);
	const vector<E>& operator[](const K& key) const;

	bool empty();
	bool contains(const K& key);
	void clear();
private:
	BTree<MultiPair<K, E>> _mMap;
};

template<typename K, typename E>
inline MultiMap<K, E>::MultiMap()
{
	//Left Blank Intentionally
}

template<typename K, typename E>
inline void MultiMap<K, E>::insert(const K& key)
{
	_mMap.insert(MultiPair<K, E>(key));
}

template<typename K, typename E>
inline void MultiMap<K, E>::remove(const K& key)
{
	_mMap.remove(MultiPair<K, E>(key));
}

template<typename K, typename E>
inline vector<E>& MultiMap<K, E>::operator[](const K& key)
{
	return _mMap.get(MultiPair<K, E>(key))._MultiEntry;
}

template<typename K, typename E>
inline const vector<E>& MultiMap<K, E>::operator[](const K& key) const
{
	return _mMap.get(MultiPair<K, E>(key))._MultiEntry;
}

template<typename K, typename E>
inline bool MultiMap<K, E>::empty()
{
	return _mMap.empty();
}

template<typename K, typename E>
inline bool MultiMap<K, E>::contains(const K& key)
{
	return _mMap.contains(MultiPair<K, E>(key));
}

template<typename K, typename E>
inline void MultiMap<K, E>::clear()
{
	_mMap.clear_tree();
}
