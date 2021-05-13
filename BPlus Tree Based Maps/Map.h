#pragma once
#include <iostream>
#include "../BPlus Tree/BPlus_Tree.h"
using namespace std;

template <typename K, typename V>
struct Pair 
{
    K key;
    V value;

    Pair(const K& k = K(), const V& v = V()) :key(k), value(v) {}

    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me)
    {
        outs << "{" << print_me.key << "|" << print_me.value << "}";
        return outs;
    }

    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key == rhs.key;
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key < rhs.key;
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key > rhs.key;
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key <= rhs.key;
    }

    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return rhs;
    }
};

template <typename K, typename V>
class Map
{
public:
    //Map Iterator
    typedef BPlusTree<Pair<K, V> > map_base;
    class Iterator {
    public:
        friend class Map;
        Iterator(typename map_base::Iterator it) :_it(it) {}
        Iterator operator ++(int unused)
        {
            return ++_it;
        }
        Iterator operator ++()
        {
            return _it++;
        }
        Pair<K, V> operator *()
        {
            return *_it;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs._it == rhs._it;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs._it != rhs._it;
        }
    private:
        typename map_base::Iterator _it;
    };

    //Map Impementation
    Map();
    //Iterators
    Map<K, V>::Iterator begin();
    Map<K, V>::Iterator end();

    //Capacity
    int size() const;
    bool empty() const;

    //Element Access
    V& operator[](const K& key);
    const V& operator[](const K& key) const;

    //Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

    //Operations:
    Map<K, V>::Iterator find(const K& key);
    bool contains(const K& key) const;

    Map<K, V>::Iterator lower_bound(const K& key);
    Map<K, V>::Iterator upper_bound(const K& key);

    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    bool is_valid() { return map.is_valid(); }

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me) {
        outs << print_me.map << endl;
        return outs;
    }
private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};

template<typename K, typename V>
inline Map<K, V>::Map(): key_count(0)
{
    //Left Blank Intentionally
}

template<typename K, typename V>
inline typename Map<K, V>::Iterator Map<K, V>::begin()
{
    return Map<K, V>::Iterator(map.begin());
}

template<typename K, typename V>
inline typename Map<K, V>::Iterator Map<K, V>::end()
{
    return Map<K, V>::Iterator(map.end());
}

template<typename K, typename V>
inline int Map<K, V>::size() const
{
    return map.size();
}

template<typename K, typename V>
inline bool Map<K, V>::empty() const
{
    return map.empty();
}

template<typename K, typename V>
inline V& Map<K, V>::operator[](const K& key)
{
    return map.get(Pair<K, V>(key)).value;
}

template<typename K, typename V>
inline const V& Map<K, V>::operator[](const K& key) const
{
    return map.get(Pair<K, V>(key)).value;
}

template<typename K, typename V>
inline void Map<K, V>::insert(const K& k, const V& v)
{
    map.insert(Pair<K, V>(k, v));
    key_count++;
}

template<typename K, typename V>
inline void Map<K, V>::erase(const K& key)
{
    map.remove(Pair<K, V>(key));
    key_count--;
}

template<typename K, typename V>
inline void Map<K, V>::clear()
{
    key_count = 0;
    map.clear_tree();
}

template<typename K, typename V>
inline typename Map<K, V>::Iterator Map<K, V>::find(const K& key)
{
    return Map<K, V>::Iterator(map.find(Pair<K,V>(key)));
}

template<typename K, typename V>
inline bool Map<K, V>::contains(const K& key) const
{
    return map.contains(Pair<K,V>(key));
}

template<typename K, typename V>
inline typename Map<K, V>::Iterator Map<K, V>::lower_bound(const K& key)
{
    for (Map<K, V>::Iterator it = begin(); it != end(); it++)
    {
        if (Pair<K, V>(key) < *it || Pair<K,V>(key) == *it)
            return it;
    }
    return end();
}

template<typename K, typename V>
inline typename Map<K, V>::Iterator Map<K, V>::upper_bound(const K& key)
{
    for (Map<K, V>::Iterator it = begin(); it != end(); it++)
    {
        if (Pair<K, V>(key) < *it)
            return it;
    }
    return end();
}
