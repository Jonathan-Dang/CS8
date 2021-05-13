#pragma once
#include <iostream>
#include <iomanip>
#include <cassert>
#include "Btree Functions.h"
using namespace std;

template <class T>
class BTree
{
public:
    BTree(bool dups = false);

    //big three:
    BTree(const BTree<T>& other);
    ~BTree();
    BTree<T>& operator =(const BTree<T>& RHS);

    //Main Function
    void insert(const T& entry);                //insert entry into the tree
    void remove(const T& entry);                //remove entry from the tree

    //Functionality
    void clear_tree();                          //clear this object (delete all nodes etc.)
    void copy_tree(const BTree<T>& other);      //copy other into this object

    bool contains(const T& entry);              //true if entry can be found in the array
    T& get(const T& entry);                     //return a reference to entry in the tree
    T& get_existing(const T& entry);            //return a reference to an entry already in the tree    
    T* find(const T& entry);                    //return a pointer to this key. NULL if not there.

    const T& get(const T& entry) const;         //Const version of get

    int size() const;                           //count the number of elements in the tree
    bool empty() const;                         //true if the tree is empty

    void print_tree(int level = 0, ostream& outs = cout) const; //print a readable version of the tree

    friend ostream& operator<<(ostream& outs, const BTree<T>& print_me) {
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
    BTree* subset[MAXIMUM + 2];                     //subtrees

    bool is_leaf() const { return child_count == 0; }   //true if this is a leaf node
    bool is_valid(bool main_root = true);

    //insert element functions
    void loose_insert(const T& entry);              //allows MAXIMUM+1 data elements in the root
    void fix_excess(int i);                         //fix excess of data elements in child i
    void grow_tree();                               //fixes the excess on the main root

    //remove element functions: 
    void loose_remove(const T& entry);              //allows MINIMUM-1 data elements in the root
    void fix_shortage(int i);                       //fix shortage of data elements in child i
    void shrink_tree();                             //fixes the shortage on the main root

    void remove_max(T& entry);                      //remove the biggest child of this tree->entry
    void rotate_left(int i);                        //transfer one element LEFT from child i | Assumes two on RIGHT child [i + 1]
    void rotate_right(int i);                       //transfer one element RIGHT from child i | Assumes two on LEFT child [i - 1]
    void merge_with_next_subset(int i);             //merge subset i with subset i+1

};

template<class T>
inline BTree<T>::BTree(bool dups) : dups_ok(dups), data_count(0), child_count(0)
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
inline BTree<T>::BTree(const BTree<T>& other)
{
    copy_tree(other);
    dups_ok = other.dups_ok;
}

template<class T>
inline BTree<T>::~BTree()
{
    clear_tree();
}

template<class T>
inline BTree<T>& BTree<T>::operator=(const BTree<T>& RHS)
{
    if (&*this == &RHS) { return this; }
    clear_tree;
    copy_tree(RHS);
    return this;
}

template<class T>
inline int BTree<T>::size() const
{
    int size = data_count;

    for (int i = 0; i < child_count; i++)
    {
        size += subset[i]->size();
    }

    return size;
}

template<class T>
inline bool BTree<T>::empty() const
{
    return (data_count == 0 && child_count == 0);
}

template<class T>
inline void BTree<T>::print_tree(int level, ostream& outs) const
{
    //print last subtree
    if (!is_leaf())
    {
        subset[child_count - 1]->print_tree(level + 1,outs);
    }

    for (int i = data_count - 1; i >= 0; i --)
    {
        //print data 
        outs << "" << setw(level * 4) << "[" << data[i] << "]" << endl;

        //print subsets
        if(!is_leaf() /*&& i <= child_count*/)
            subset[i]->print_tree(level + 1, outs);
    }
}

template<class T>
inline bool BTree<T>::is_valid(bool main_root)
{
    if (main_root)
    {
        if (data_count != MINIMUM)
            cout << true << " ";
        else
            cout << false << " ";
    }
    else
    {
        if (is_leaf)
        {
            if (data_count < MAXIMUM && data_count >= MINIMUM)
                cout << true << " ";
        }
        else
        {
            if (data_count < MAXIMUM && child_count < MAXIMUM + 1)
            {
                if (child_count == data_count + 1)
                {
                    bool check = true;
                    while (check)
                    {
                        int i = 0;
                        for (int t = 0; i < data_count; i++)
                        {
                            if (subset[i]->data[t] > data[t])
                            {
                                cout << false << " ";
                                check = false;
                                break;
                            }
                            else
                            {
                                cout << true << " ";
                                break;
                            }
                        }
                        i++;
                        if (i == data_count - 1)
                        {
                            cout << "NODE CORRECT\n";
                            break;
                        }
                    }

                }
                else
                    cout << false << " ";
            }
        }
        for (int i = 0; i < data_count; i++)
        {
            subset[i]->is_valid(false);
        }
    }
}

template<class T>
inline void BTree<T>::loose_insert(const T& entry)
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);

    if (found)
    {
        if (dups_ok)
        {
            //Dups loose insert
            data[i] = entry;    
        }
        else
        {
            //No Dups allowed, so dumping insertion
            return;
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
inline void BTree<T>::fix_excess(int i) //Child count isn't updated | why is the subset of 0 and 1 of subset[0] have 20 children 
{
    //Create a new Child
    BTree<T>* fix = new BTree<T>(dups_ok);

    //Split subset[i] to child
    split(subset[i]->data, subset[i]->data_count
        , fix->data, fix->data_count);

    split(subset[i]->subset, subset[i]->child_count
        , fix->subset, fix->child_count);

    //Insert and connect the child
    insert_item(subset, i + 1, child_count, fix);

    //detach last bit of subset[i]
    T hold;
    detach_item(subset[i]->data, subset[i]->data_count, hold);

    //attach it to this data set
    insert_item(data, i, data_count, hold); //Why.... god damn it pointer/arrays
}

template<class T>
inline void BTree<T>::grow_tree()
{
    //Make a new BTree node
    BTree<T>* grow = new BTree<T>(dups_ok);

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
inline void BTree<T>::loose_remove(const T& entry)
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);

    if (found)
    {
        if (is_leaf())
        { 
            T hold;
            delete_item(data, i, data_count, hold);
        }
        else
        {
            subset[i]->remove_max(data[i]);
            if (subset[i]->data_count < MINIMUM)
                fix_shortage(i);
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
                fix_shortage(i);
        }
    }
}

template<class T>
inline void BTree<T>::fix_shortage(int i)
    {
    if (i < child_count - 1 && subset[i + 1]->data_count > MINIMUM)
        rotate_left(i + 1);
    else if (0 < i && i < child_count - 1
        && subset[i - 1]->data_count > MINIMUM)
        rotate_right(i - 1);
    else if (subset[i + 1] != nullptr && i < child_count - 1)
        merge_with_next_subset(i);
    else
        merge_with_next_subset(i - 1);
}

template<class T>
inline void BTree<T>::shrink_tree()
{
    //Point a Pointer at only child
    BTree<T>* shrink_ptr = subset[0];

    //Copy all aspects of shrink_ptr to here
    copy_array(data, shrink_ptr->data, data_count, shrink_ptr->data_count);
    copy_array(subset, shrink_ptr->subset, child_count, shrink_ptr->child_count);

    shrink_ptr->child_count = 0;
    shrink_ptr->data_count = 0;

    //Delete the pointer
    delete shrink_ptr;
}

template<class T>
inline void BTree<T>::insert(const T& entry)
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
inline void BTree<T>::remove(const T& entry)
{
    loose_remove(entry);
    if (data_count < MINIMUM)
    {
        shrink_tree();
    }
}

template<class T>
inline void BTree<T>::clear_tree()
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

    //return :^)
    return;
}

template<class T>
inline void BTree<T>::copy_tree(const BTree<T>& other)
{
    //Copy at this Level
    copy_array(data, other.data, data_count, other.data_count);

    //Copying in recursion
    child_count = other.child_count;
    for (int i = 0; i < other.child_count; i++)
    {
        subset[i] = new BTree;
        subset[i]->copy_tree(other.subset[i]);
    }
}

template<class T>
inline bool BTree<T>::contains(const T& entry)
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);

    if (found)
        return true;
    else
    {
        if (is_leaf())
            return false;

        return subset[i]->contains(entry);
    }
}

template<class T>
inline T& BTree<T>::get(const T& entry)
{
    if (!contains(entry))
        insert(entry);

    return get_existing(entry);
}

template<class T>
inline T& BTree<T>::get_existing(const T& entry)
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);

    if (found)
        return data[i];
    else
    {
        return subset[i]->get_existing(entry);
    }
}

template<class T>
inline T* BTree<T>::find(const T& entry)
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count && data[i] == entry);
    
    if (found)
    {
        return &data[i];
    }
    else
    {
        if (is_leaf())
            return nullptr;

        return subset[i]->find(entry);
    }

}

template<class T>
inline const T& BTree<T>::get(const T& entry) const
{
    int i = first_ge(data, data_count, entry);
    bool found = (i < data_count&& data[i] == entry);

    if (found)
        return data[i];
    else
    {
        if (is_leaf())
            return NULL;
        return subset[i]->get(entry);
    }
}

template<class T>
inline void BTree<T>::remove_max(T& entry)
{
    if (!is_leaf())
    {
        subset[child_count - 1]->remove_max(entry);
        if (subset[child_count - 1]->data_count < MINIMUM)
        {
            fix_shortage(child_count - 1);

            return;
        }
    }

    detach_item(data, data_count, entry);
    return;
}

template<class T>
inline void BTree<T>::rotate_left(int i) //Right Child has 2
{
    //Hold Assertions
    assert(0 < i);
    assert(i < child_count);
    assert(subset[i]->data_count > MINIMUM);

    //Bring first item of subset[i] to here, append.
    T hold;
    delete_item(subset[i]->data, 0, subset[i]->data_count, hold);

    //Replace data[i - 1]'s data
    T DHere;
    delete_item(data, i - 1, data_count, DHere);
    insert_item(data, i - 1, data_count, hold);
    attach_item(subset[i - 1]->data, subset[i - 1]->data_count, DHere);

    //If Needed
    if (!is_leaf() && subset[i]->child_count > subset[i]->data_count + 1)
    {
        BTree<T>* move;
        delete_item(subset[i]->subset, 0, subset[i]->child_count, move);
        attach_item(subset[i - 1]->subset, subset[i - 1]->child_count, move);
    }
}

template<class T>
inline void BTree<T>::rotate_right(int i) //Left Child has 2
{
    //Hold Assertions
    assert(i < child_count - 1);
    assert(subset[i]->data_count > MINIMUM);

    //Bring Last item of subset[i] to here, 
    T hold;
    detach_item(subset[i]->data, subset[i]->data_count, hold);

    //Replace data[i+1]'s data
    T DHere;
    delete_item(data, i + 1, data_count, DHere);
    insert_item(data, i, data_count, hold);
    insert_item(subset[i+1]->data, i, subset[i+1]->data_count, DHere);

    //If Needed
    if (!is_leaf() && subset[i]->child_count > subset[i]->data_count + 1)
    {
        BTree<T>* move;
        detach_item(subset[i]->subset, subset[i]->child_count, move);
        insert_item(subset[i + 1]->subset, 0, subset[i + 1]->child_count, move);
    }
}

template<class T>
inline void BTree<T>::merge_with_next_subset(int i)
{
    //Take down data[i] to subset[i]->data
    T hold;
    detach_item(data, data_count, hold);
    attach_item(subset[i]->data, subset[i]->data_count, hold);

    //Merging Data
    merge(subset[i]->data, subset[i]->data_count,
        subset[i + 1]->data, subset[i + 1]->data_count);

    //Merging Subsets
    merge(subset[i]->subset, subset[i]->child_count,
        subset[i + 1]->subset, subset[i + 1]->child_count);

    //updating child count
    BTree* merg = subset[i + 1];
    //delete [] merg;
    delete merg;
    child_count--;
}
