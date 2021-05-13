#pragma once
#include <iostream>
#include <vector>
#include "../BPlus Tree/BPlus_Tree.h"
using namespace std;

template <typename K, typename V>
struct MPair {
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
     //--------------------------------------------------------------------------------
    MPair(const K& k = K()) :key(k) {}
    MPair(const K& k, const V& v) :key(k)
    {
        value_list += v;
    }
    MPair(const K& k, const vector<V>& vlist) :key(k), value_list(vlist) {}
    //--------------------------------------------------------------------------------

    //You'll need to overlod << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me)
    {
        outs << "{" << print_me.key << "|" << print_me.value_list << "}";
        return outs;
    }

    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key == rhs.key;
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key < rhs.key;
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key <= rhs.key;
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key > rhs.key;
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return rhs;
    }
};

template <typename K, typename V>
class MMap
{
public:
    //MMap Iterators
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator 
    {
    public:
        friend class MMap;
        Iterator(typename map_base::Iterator it) :_it(it) {}
        Iterator operator ++(int unused)
        {
            return ++_it;
        }
        Iterator operator ++()
        {
            return _it++;
        }
        MPair<K, V> operator *()
        {
            return  *_it;
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

    //MMap Implementation
    MMap();

    //Iterators
    MMap<K, V>::Iterator begin();
    MMap<K, V>::Iterator end();

    //Capacity
    int size() const;
    bool empty() const;

    //Element Access
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);

    //Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

    //  Operations:
    bool contains(const K& key) const;
    vector<V>& get(const K& key);

    MMap<K, V>::Iterator find(const K& key);
    int count(const K& key);

    MMap<K, V>::Iterator lower_bound(const K& key);
    MMap<K, V>::Iterator upper_bound(const K& key);
    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound   
    //    equal_range:

    bool is_valid() { return mmap.is_valid(); }

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me) 
    {
        outs << print_me.mmap << endl;
        return outs;
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};

template<typename K, typename V>
inline MMap<K, V>::MMap()
{
    //Left Blank Intentionally
}

template<typename K, typename V>
inline typename MMap<K,V>::Iterator MMap<K, V>::begin()
{
    return MMap<K, V>::Iterator(mmap.begin());
}

template<typename K, typename V>
inline typename MMap<K, V>::Iterator MMap<K, V>::end()
{
    return MMap<K, V>::Iterator(mmap.end());
}

template<typename K, typename V>
inline int MMap<K, V>::size() const
{
    return mmap.size();
}

template<typename K, typename V>
inline bool MMap<K, V>::empty() const
{
    return mmap.empty();
}

template<typename K, typename V>
inline const vector<V>& MMap<K, V>::operator[](const K& key) const
{
    return mmap.get(MPair<K, V>(key)).value_list;
}

template<typename K, typename V>
inline vector<V>& MMap<K, V>::operator[](const K& key)
{
    return mmap.get(MPair<K, V>(key)).value_list;
}

template<typename K, typename V>
inline void MMap<K, V>::insert(const K& k, const V& v)
{
    mmap.get(MPair<K, V>(k)).value_list += v;
}

template<typename K, typename V>
inline void MMap<K, V>::erase(const K& key)
{
    mmap.remove(MPair<K, V>(key));
}

template<typename K, typename V>
inline void MMap<K, V>::clear()
{
    mmap.clear_tree();
}

template<typename K, typename V>
inline bool MMap<K, V>::contains(const K& key) const
{
    return mmap.contains(MPair<K,V>(key));
}

template<typename K, typename V>
inline vector<V>& MMap<K, V>::get(const K& key)
{
    return mmap.get(MPair<K, V>(key)).value_list;
}

template<typename K, typename V>
inline typename MMap<K, V>::Iterator MMap<K, V>::find(const K& key)
{
    return MMap<K, V>::Iterator(mmap.find((MPair<K,V>(key))));
}

template<typename K, typename V>
inline int MMap<K, V>::count(const K& key)
{
    MPair<K, V> found = mmap.get(MPair<K, V>(key));
    return found.value_list.size();
}

template<typename K, typename V>
inline typename MMap<K, V>::Iterator MMap<K, V>::lower_bound(const K& key)
{
    for (MMap<K, V>::Iterator it = begin(); it != end(); it++)
    {
        if (MPair<K, V>(key) < *it || MPair<K,V>(key) == *it)
            return it;
    }
    return end();
}

template<typename K, typename V>
inline typename MMap<K, V>::Iterator MMap<K, V>::upper_bound(const K& key)
{
    for (MMap<K, V>::Iterator it = begin(); it != end(); it++)
    {
        if (MPair<K, V>(key) < *it)
            return it;
    }
    return end();
}
