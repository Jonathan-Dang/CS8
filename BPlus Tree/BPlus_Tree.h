#pragma once
#pragma once
#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdlib.h>
#include "../BTree/BTree Functions.h"
using namespace std;

template <class T>
class BPlusTree
{
public:
    //BPlusTree::Iterator
    class Iterator {
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it = NULL, int _key_ptr = 0) :it(_it), key_ptr(_key_ptr) {}

        T operator *() 
        {
            assert(key_ptr < it->data_count);
            return it->data[key_ptr];
        }

        Iterator operator++(int un_used) //p++
        {
            Iterator temp = *this;

            if (key_ptr >= it->data_count - 1)
            {
                it = it->next;
                key_ptr = 0;
            }
            else
                key_ptr++;

            return temp;
        }

        Iterator operator++() //++p
        {
            if (key_ptr >= it->data_count - 1)
            {
                it = it->next;
                key_ptr = 0;
            }
            else
                key_ptr++;

            return (*this);
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs) 
        {
            return (lhs.it == rhs.it) && (lhs.key_ptr == rhs.key_ptr);
        }

        friend bool operator !=(const Iterator& lhs, const Iterator& rhs) 
        {
            return (lhs.it != rhs.it) || (lhs.key_ptr != rhs.key_ptr);
        }

        void print_Iterator() 
        {
            cout << it->data[key_ptr];
        }

        bool is_null() { return !it; }
    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    //BPlusTree<T>
    BPlusTree(bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    //Iterator Functions
    BPlusTree<T>::Iterator begin();             //Iterates the smallest leaf of the tree
    BPlusTree<T>::Iterator end();               //Iterates NULL

    //Main Function
    void insert(const T& entry);                //insert entry into the tree
    void remove(const T& entry);                //remove entry from the tree

    //Functionality
    void clear_tree();                          //clear this object (delete all nodes etc.)
    void copy_tree(const BPlusTree<T>& other);  //copy other into this object

    bool contains(const T& entry) const;        //true if entry can be found in the array
    T& get(const T& entry);                     //return a reference to entry in the tree
    T& get_existing(const T& entry);            //return a reference to an entry already in the tree    
    BPlusTree<T>::Iterator find(const T& entry);//return an Iterator to the entry in the tree

    const T& get(const T& entry) const;         //Const version of get

    int size() const;                           //count the number of elements in the tree
    bool empty() const;                         //true if the tree is empty
    bool is_valid();

    void print_tree(int level = 0, ostream& outs = cout) const; //print a readable version of the tree

    friend ostream& operator<<(ostream& outs, const BPlusTree<T>& print_me) 
    {
        print_me.print_tree(0, outs);
        return outs;
    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                                   //true if duplicate keys may be inserted
    int data_count;                                 //number of data elements
    T data[MAXIMUM + 1];                            //holds the keys
    int child_count;                                //number of children
    BPlusTree* subset[MAXIMUM + 2];                 //sub BPlusTrees
    BPlusTree* next;

    bool is_leaf() const { return child_count == 0;}//true if this is a leaf node
    bool is_valid_last_leaf(const T& compare);      //Compares the value to all of the largest leaf
    void copy(const BPlusTree<T>& other, BPlusTree<T>*& last_node = nullptr);

    //insert element functions
    void loose_insert(const T& entry);              //allows MAXIMUM+1 data elements in the root
    void fix_excess(int i);                         //fix excess of data elements in child i
    void grow_tree();                               //fixes the excess on the main root

    //remove element functions: 
    void loose_remove(const T& entry);              //allows MINIMUM-1 data elements in the root
    BPlusTree<T>* fix_shortage(int i);                       //fix shortage of data elements in child i
    void shrink_tree();                             //fixes the shortage on the main root
    void smallest(T& replace);                      //Replaces the variable with the smallest unit of this chain

    void rotate_left(int i);                        //transfer one element LEFT from child i | Assumes two on RIGHT child [i + 1]
    void rotate_right(int i);                       //transfer one element RIGHT from child i | Assumes two on LEFT child [i - 1]
    BPlusTree<T>* merge_with_next_subset(int i);    //merge subset i with subset i+1
};

template<class T>
inline BPlusTree<T>::BPlusTree(bool dups) : dups_ok(dups), data_count(0)
                                                , child_count(0), next(nullptr)
{
    //Default Inputs for T variable type
    for (int i = 0; i < MAXIMUM + 1; i++)
    {
        data[i] = T();
    }

    //Setting subset to nullptr
    for (int i = 0; i < MAXIMUM + 2; i++)
    {
        subset[i] = nullptr;
    }
}

template<class T>
inline BPlusTree<T>::BPlusTree(const BPlusTree<T>& other)
{
    copy_tree(other);
    dups_ok = other.dups_ok;
}

template<class T>
inline BPlusTree<T>::~BPlusTree()
{
    clear_tree();
}

template<class T>
inline BPlusTree<T>& BPlusTree<T>::operator=(const BPlusTree<T>& RHS)
{
    clear_tree();
    copy_tree(RHS);
    return *this;
}

template<class T>
inline typename BPlusTree<T>::Iterator BPlusTree<T>::begin()
{
    if (!is_leaf())
        return subset[0]->begin();
    else
        return BPlusTree<T>::Iterator(this, 0);
}

template<class T>
inline typename BPlusTree<T>::Iterator BPlusTree<T>::end()
{
    return BPlusTree<T>::Iterator(nullptr, NULL);
}

template<class T>
inline int BPlusTree<T>::size() const
{
    int size = data_count;

    for (int i = 0; i < child_count; i++)
    {
        size += subset[i]->size();
    }

    return size;
}

template<class T>
inline bool BPlusTree<T>::empty() const
{
    return (data_count == 0 && child_count == 0);
}

template<class T>
inline void BPlusTree<T>::print_tree(int level, ostream& outs) const
{
    //print last suBPlusTree
    if (!is_leaf())
    {
        subset[child_count - 1]->print_tree(level + 1, outs);
    }

    for (int i = data_count - 1; i >= 0; i--)
    {
        //print data 
        outs << "" << setw(level * 4) << "[" << data[i] << "]" << endl;

        //print subsets
        if (!is_leaf() /*&& i <= child_count*/)
            subset[i]->print_tree(level + 1, outs);
    }
}

template<class T>
inline bool BPlusTree<T>::is_valid()
{
    if (is_leaf())
        return true;
    
    //Check if all data points here are less than or equal to largest leaf
    for (int i = 0; i < data_count; i++)
    {
        if (!is_valid_last_leaf(data[i]))
            return false;
    }

    for (int i = 0; i < subset[0]->data_count; i++)
    {
        if (data[0] < subset[0]->data[i])
            return false;
    }

    for (int i = 0; i < data_count; i++)
    {
        if (!contains(data[i]))
            return false;
    }

    for (int i = 0; i < child_count; i++)
    {
        if (!subset[i]->is_valid())
            return false;
    }
    return true;
}

template<class T>
inline bool BPlusTree<T>::is_valid_last_leaf(const T& compare)
{
    if (!is_leaf())
        return subset[child_count - 1]->is_valid_last_leaf(compare);

    for (int i = 0; i < data_count; i++)
    {
        if (compare > data[i])
            return false;
    }
    return true;
}

template<class T>
inline void BPlusTree<T>::copy(const BPlusTree<T>& other, BPlusTree<T>*& last_node)
{
    //Copy at this Level
    copy_array(data, other.data, data_count, other.data_count);

    //Deal with Last Node/ Next Node ordeal
    if (other.is_leaf())
    {
        if (last_node != nullptr)
        {
            last_node->next = this;
        }
        last_node = this;
    }

    child_count = other.child_count;
    for (int i = 0; i < other.child_count; i++)
    {
        BPlusTree<T>* temp = new BPlusTree<T>;
        temp->copy(*other.subset[i], last_node);
        subset[i] = temp;
    }
}

template<class T>
inline void BPlusTree<T>::loose_insert(const T& entry)
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count&& data[i] == entry);

    if (found)
    {
        if (is_leaf())
        {
            if (dups_ok)
            {
                //Dups loose insert
                insert_item(data, i, data_count, entry);
            }
            else
            {
                //No Dups allowed, updating item
                data[i] = entry;
            }
        }
        else
        {
            subset[i + 1]->loose_insert(entry);
            if (subset[i + 1]->data_count > MAXIMUM)
                fix_excess(i + 1);
        }
    }
    else
    {
        if (is_leaf())
        {
            //Leaf Loose Insert
            insert_item(data, i, data_count, entry);
        }
        else
        {
            //Not Leaf Loose Insert
            subset[i]->loose_insert(entry);
            if (subset[i]->data_count > MAXIMUM)
            {
                fix_excess(i);
            }
        }
    }
}

template<class T>
inline void BPlusTree<T>::fix_excess(int i)
{
    //Create a new Child
    BPlusTree<T>* fix = new BPlusTree<T>(dups_ok);

    //Split subset[i] to child
    split(subset[i]->data, subset[i]->data_count
        , fix->data, fix->data_count);

    split(subset[i]->subset, subset[i]->child_count
        , fix->subset, fix->child_count);

    //Insert and connect the child
    insert_item(subset, i + 1, child_count, fix);

    //Obtain middle Value from subset[i]
    T hold = T();
    detach_item(subset[i]->data, subset[i]->data_count, hold);

    //insert it to this data set
    insert_item(data, i, data_count, hold); 
        
    //Leaf inspection
    if (subset[i]->is_leaf() || is_leaf())
    {
        insert_item(subset[i + 1]->data, 0, subset[i + 1]->data_count, hold);

        //Deal With Pointers
        subset[i + 1]->next = subset[i]->next;
        subset[i]->next = subset[i + 1];
    }
}

template<class T>
inline void BPlusTree<T>::grow_tree()
{
    //Make a new BPlusTree node
    BPlusTree<T>* grow = new BPlusTree<T>(dups_ok);

    //Shallow Copy
    copy_array(grow->subset, subset, grow->child_count, child_count);
    copy_array(grow->data, data, grow->data_count, data_count);

    //Set Data_count to 0 and Child_count to 1
    data_count = 0;
    child_count = 1;

    //Set subset[0] to new node
    subset[0] = grow;
}

template<class T>
inline void BPlusTree<T>::loose_remove(const T& entry)
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count&& data[i] == entry);

    if (found)
    {
        if (is_leaf())
        {
            T hold = T();
            delete_item(data, i, data_count, hold);
        }
        else
        {
            subset[i + 1]->loose_remove(entry);
            if (subset[i + 1]->data_count < MINIMUM)
            {
                //Fix Shortage Series
                BPlusTree<T>* temp = fix_shortage(i + 1);

                for (int t = 0; t < data_count; t++)
                {
                    if (data[t] == entry)
                        subset[i + 1]->smallest(data[t]);
                }
                for (int t = 0; t < temp->data_count; t++)
                {
                    if (temp->data[t] == entry)
                    {
                        if (temp->is_leaf())
                        {
                            temp->data[t] = data[i];
                        }
                        else
                        {
                            int pos = first_ge(temp->data, temp->data_count, entry);
                            temp->subset[pos + 1]->smallest(temp->data[t]);
                        }
                    }
                }
            }
            else
            {
                subset[i + 1]->smallest(data[i]);
            }
        }
    }
    else
    {
        if (is_leaf())
        {
            return;
        }
        else
        {
            subset[i]->loose_remove(entry);
            if (subset[i]->data_count < MINIMUM)
            {
                fix_shortage(i);
            }
        }
    }
}

template<class T>
inline BPlusTree<T>* BPlusTree<T>::fix_shortage(int i)
{
    if (i < child_count - 1 && subset[i + 1]->data_count > MINIMUM)
    {
        rotate_left(i + 1);
        return subset[i];
    }    
    else if (0 < i && subset[i - 1]->data_count > MINIMUM)
    {
        rotate_right(i - 1);
        return subset[i];
    }
    else if (i > 0 && subset[i - 1] != nullptr)
    {
        return merge_with_next_subset(i - 1);
    }
    else
    {
        return merge_with_next_subset(i);
    }
}

template<class T>
inline void BPlusTree<T>::shrink_tree()
{
    //Point a Pointer at only child
    BPlusTree<T>* shrink_ptr = subset[0];

    //Copy all aspects of shrink_ptr to here
    copy_array(data, shrink_ptr->data, data_count, shrink_ptr->data_count);
    copy_array(subset, shrink_ptr->subset, child_count, shrink_ptr->child_count);

    shrink_ptr->child_count = 0;
    shrink_ptr->data_count = 0;

    //Delete the pointer
    delete shrink_ptr;
}

template<class T>
inline void BPlusTree<T>::smallest(T& replace)
{
    if (is_leaf())
    {
        replace = data[0];
    }
    else
    {
        subset[0]->smallest(replace);
    }
}
    
template<class T>
inline void BPlusTree<T>::insert(const T& entry)
{
    //Loose Insert at this level
    loose_insert(entry);

    //Grow the tree if needed
    if (data_count > MAXIMUM)
    {
        grow_tree();
        fix_excess(0);
    }
}

template<class T>
inline void BPlusTree<T>::remove(const T& entry)
{
    loose_remove(entry);
    if (!is_leaf () && data_count < MINIMUM)
    {
        shrink_tree();
    }
}

template<class T>
inline void BPlusTree<T>::clear_tree()
{
    //Recursively call all children's clear_tree function.
    if (!is_leaf())
    {
        for (int i = 0; i < child_count; i++)
        {
            subset[i]->clear_tree();
            delete subset[i];
        }
    }

    //"Reset" to all default inputs.
    for (int i = 0; i < data_count; i++)
    {
        data[i] = T();
    }

    //update trackers
    data_count = 0;
    child_count = 0;
    next = nullptr;

    //return :^)
    return;
}

template<class T>
inline void BPlusTree<T>::copy_tree(const BPlusTree<T>& other)
{
    BPlusTree<T>* temp = nullptr;
    copy(other,temp);
}

template<class T>
inline bool BPlusTree<T>::contains(const T& entry) const
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count&& data[i] == entry);

    if (found)
    {
        if (is_leaf())
            return true;
        else
            return subset[i + 1]->contains(entry);
    }
    else
    {
        if (is_leaf())
            return false;
        else
            return subset[i]->contains(entry);
    }

    return false;
}

template<class T>
inline T& BPlusTree<T>::get(const T& entry)
{
    if (!contains(entry))
        insert(entry);

    return get_existing(entry);
}

template<class T>
inline T& BPlusTree<T>::get_existing(const T& entry)
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count&& data[i] == entry);

    if (found)
    {
        if (is_leaf())
            return data[i];
        else
            return subset[i + 1]->get_existing(entry);
    }
    else
    {
        if (is_leaf())
        {
            cout << "ERROR!!!\nITEM NOT FOUND!\n";
            exit(EXIT_FAILURE);
        }
        else
            return subset[i]->get_existing(entry);
    }
}

template<class T>
inline typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T& entry)
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count&& data[i] == entry);

    if (found)
    {
        if (is_leaf())
            return BPlusTree<T>::Iterator(this, i);
        else
            return subset[i + 1]->find(entry);
    }
    else
    {
        if (is_leaf())
            return BPlusTree<T>::Iterator(nullptr, NULL);
        else
            return subset[i]->find(entry);
    }
}

template<class T>
inline const T& BPlusTree<T>::get(const T& entry) const
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count&& data[i] == entry);

    if (found)
    {
        if (is_leaf())
            return data[i];
        else
            return subset[i + 1]->get(entry);
    }
    else
    {
        if (is_leaf())
            return NULL;
        else
            return subset[i]->get(entry);
    }
}

template<class T>
inline void BPlusTree<T>::rotate_left(int i) //Right Child has 2 | subset[i] is fat, subset[i - 1] is skinny
{
    //Hold Assertions
    assert(0 < i);
    assert(i < child_count);
    assert(subset[i]->data_count > MINIMUM);

    //Bring first item of subset[i] to here, append.
    T hold = T();
    delete_item(subset[i]->data, 0, subset[i]->data_count, hold);

    //Same Rotate left as Btree
    T DHere = T();
    delete_item(data, i - 1, data_count, DHere);
    insert_item(data, i - 1, data_count, hold);
    attach_item(subset[i - 1]->data, subset[i - 1]->data_count, DHere);

    //If [i] is leaf, update data[i - 1]
    if (subset[i]->is_leaf())
    {
        data[i - 1] = subset[i]->data[0];
    }

    //If Needed
    if (!is_leaf() && subset[i]->child_count > subset[i]->data_count + 1)
    {
        BPlusTree<T>* move = nullptr;
        delete_item(subset[i]->subset, 0, subset[i]->child_count, move);
        attach_item(subset[i - 1]->subset, subset[i - 1]->child_count, move);
    }
}

template<class T>
inline void BPlusTree<T>::rotate_right(int i) //Left Child has 2 | subset[i] is fat, subset[i + 1] is skinny
{
    //Hold Assertions
    assert(i < child_count - 1);
    assert(subset[i]->data_count > MINIMUM);

    //Bring Last item of subset[i] to here, 
    T hold = T();
    detach_item(subset[i]->data, subset[i]->data_count, hold);

    //Same old Rotate from BTree
    T DHere = T();
    delete_item(data, i, data_count, DHere);
    insert_item(data, i, data_count, hold);
    attach_item(subset[i + 1]->data, subset[i + 1]->data_count, DHere);

    //Update if [i+1] is leaf
    if (subset[i + 1]->is_leaf())
    {
        data[i] = subset[i + 1]->data[0];
    }

    //If Needed
    if (!is_leaf() && subset[i]->child_count > subset[i]->data_count + 1)
    {
        BPlusTree<T>* move = nullptr;
        detach_item(subset[i]->subset, subset[i]->child_count, move);
        insert_item(subset[i + 1]->subset, 0, subset[i + 1]->child_count, move);
    }
}

template<class T>
inline BPlusTree<T>* BPlusTree<T>::merge_with_next_subset(int i)
{
    //delete item BUT DO NOT APPEND!
    T hold = T();
    delete_item(data, i, data_count, hold);

    if (!subset[i]->is_leaf())
        attach_item(subset[i]->data, subset[i]->data_count, hold);

    //Merging Data
    merge(subset[i]->data, subset[i]->data_count,
        subset[i + 1]->data, subset[i + 1]->data_count);

    //Merging Subsets
    merge(subset[i]->subset, subset[i]->child_count,
        subset[i + 1]->subset, subset[i + 1]->child_count);

    //updating child count
    BPlusTree<T>* merg = nullptr;
    subset[i]->next = subset[i + 1]->next;
    delete_item(subset, i + 1, child_count, merg);
    delete merg;
    return subset[i];
}
