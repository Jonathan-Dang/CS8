#pragma once
#include <iostream>
#include "../Vector/Vector.h"
#include <iomanip>
using namespace std;


//--------------------------------------------------------------------------//
//                            TREE NODE STRUCTURE                           //
//--------------------------------------------------------------------------//

template <typename T>
struct tree_node {
    T _item;
    tree_node<T>* _left;
    tree_node<T>* _right;
    int _height;
    int balance_factor() {
        //balance factor = height of the right subtree 
        //                        - the height of the left subtree
        //a NULL child has a height of -1
        //a leaf has a height of 0
        if (_left && _right)
            return _left->height() - _right->height();
        else if (_left)
            return _left->height() + 1;
        else if (_right)
            return -1 - _right->height();

        return 0;
        //NOTE: Right heavy is always positive, Left heavy is always Negative,
        //      ZERO MEANS BALANCED
    }

    int height() {
        // Height of a node is 1 + height of the "taller" child
        //A leaf node has a height of zero: 1 + max(-1,-1)
        if (_left && _right)
            return max(_left->_height, _right->_height) + 1;
        else if (_left)
            return _left->_height + 1;
        else if (_right)
            return _right->_height + 1;

        return 0;
    }

    int update_height() 
    {
        //set the _height member variable (call height();)
        _height = height();
        return _height;
    }

    tree_node(T item = T(), tree_node* left = nullptr,
        tree_node* right = nullptr) :
        _item(item), _left(left), _right(right)
    {
        //don't forget to set the _height.
        _height = 0;
    }

    friend ostream& operator <<(ostream& outs,
        const tree_node<T>& t_node) 
    {
        outs << "|" << t_node._item << "|";
        return outs;
    }

    friend ostream& operator <<(ostream& outs, const tree_node<T>*& t)
    {
        outs << "|" << t->_item << "|";
        return outs;
    }
};

//--------------------------------------------------------------------------//
//                          TREE NODE FUNCTION CALLS                        //
//--------------------------------------------------------------------------//

template <typename T>
void tree_insert(tree_node<T>*& root, const T& insert_me);

template <typename T>
void tree_insert_balanced(tree_node<T>*& root, const T& insert_me);

template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target);

template <typename T>
bool tree_search(tree_node<T>* root, const T& target,
    tree_node<T>*& found_ptr);

template<typename T>
void tree_print(tree_node<T>* root, int level = 0,
    ostream& outs = cout);

template<typename T>       //prints detailes info about each node
void tree_print_debug(tree_node<T>* root, int level = 0,
    ostream& outs = cout);

template <typename T>       //clear the tree
void tree_clear(tree_node<T>*& root);

template <typename T>       //erase target from the tree
bool tree_erase(tree_node<T>*& root, const T& target);

template <typename T>
bool tree_erase_balanced(tree_node<T>*& root, const T& target);

template <typename T>       //erase rightmost node from the tree
                            // store the item in max_value
void tree_remove_max(tree_node<T>*& root, T& max_value);

template <typename T>       //return copy of tree pointed to by root
tree_node<T>* tree_copy(const tree_node<T>* root);

template <typename T>       //Add tree src to dest
void tree_add(tree_node<T>*& dest, const tree_node<T>* src);

template <typename T>       // sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int size);

template <typename T>
tree_node<T>* tree_sorted_list(const T* a, int low, int high);

template <typename T>
void tree_to_sorted_list(const tree_node<T>* root, T*& array); //INCORRECT

template <typename T>
void tree_to_sorted_list(const tree_node<T>* root, Vector<T>& v);

template <typename T>
bool avl_valid(tree_node<T>* root);

// ---------------- ROTATIONS --------------------------
template <typename T>
tree_node<T>* rotate_right(tree_node<T>*& root);

template <typename T>
tree_node<T>* rotate_left(tree_node<T>*& root);

template <typename T>
tree_node<T>* rotate(tree_node<T>*& root); //decide which rotate is needed based on balance factor

//--------------------------------------------------------------------------//
//                      TREE NODE FUNCTION DEFINITIONS                      //
//--------------------------------------------------------------------------//

template <typename T>
void tree_insert(tree_node<T>*& root, const T& insert_me)
{
    if (!root)
    {
        root = new tree_node<T>(insert_me);
    }
    else if (insert_me < root->_item)
    {
        tree_insert(root->_left, insert_me);
    }
    else
    {
        tree_insert(root->_right, insert_me);
    }
    root->update_height();
}

template<typename T>
inline void tree_insert_balanced(tree_node<T>*& root, const T& insert_me)
{
    if (!root)
    {
        root = new tree_node<T>(insert_me);
        return;
    }

    if (tree_search(root, insert_me))
        return;

    if (insert_me < root->_item)
    {
        tree_insert_balanced(root->_left, insert_me);
    }
    else if (insert_me > root->_item)
    {
        tree_insert_balanced(root->_right, insert_me);
    }
    else
    {
        return;
    }

    root->update_height();
    root = rotate(root);
}

template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target)
{
    if (!root)
    {
        return root;
    }

    if (root->_item == target)
    {
        return root;
    }

    if (target < root->_item)
    {
        return tree_search(root->_left, target);
    }
    
    if (target > root->_item)
    {
        return tree_search(root->_right, target);
    }

    root->update_height();

    return root;
}

template <typename T>
bool tree_search(tree_node<T>* root, const T& target,
    tree_node<T>*& found_ptr)
{   
    if (!root)
    {
        return false;
    }

    if (root->_item == target)
    {
        found_ptr = root;
        return true;
    }

    if (target < root->_item)
    {
        return tree_search(root->_left, target, found_ptr);
    }

    if (target > root->_item)
    {
        return tree_search(root->_right, target, found_ptr);
    }

    return false;
}

template<typename T>
void tree_print(tree_node<T>* root, int level,
    ostream& outs)
{
    if (root)
    {
        tree_print(root->_right, level + 1);
        outs << setw(4*level) << " " << "[" << root->_item << "]" << endl;
        tree_print(root->_left, level + 1);
    }
}

template<typename T>       //prints detailes info about each node
void tree_print_debug(tree_node<T>* root, int level,
    ostream& outs)
{
    if (root)
    {
        tree_print(root->_right, level + 1);
        outs << setw(3 * level) << "" << "[" << root->_item << "]" << endl;
        tree_print(root->_left, level + 1);
    }
}

template <typename T>       //clear the tree
void tree_clear(tree_node<T>*& root)
{
    if (root)
    {
        tree_clear(root->_left);
        tree_clear(root->_right);
        delete root;
        root = NULL;
    }
}

template <typename T>       //erase target from the tree 
                            //NOTE: Removes Leaf Node and places 
                            //item into removed node!
bool tree_erase(tree_node<T>*& root, const T& target)
{
    static tree_node<T>* p;
    if (!root)
    {
        return false;
    }

    if (target < root->_item)
    {
        if (root->_left && root->_left->_item == target)
        {
            p = root;
        }
        return tree_erase(root->_left, target);
    }
    if (target > root->_item)
    {
        if (root->_right && root->_right->_item == target)
        {
            p = root;
        }
        return tree_erase(root->_right, target);
    }

    if (target == root->_item)
    {
        if (!root->_left)
        {
            if (!root->_right)
            {
                delete root;
                root = NULL;
                return true;
            }
            else
            {
                tree_node<T>* temp = root->_right;
                delete root;
                root = NULL;
                root = temp;
                root->update_height();
                return true;
            }
        }
        else
        {
            T change;
            tree_remove_max(root->_left, change);
            root->_item = change;
            root->update_height();
            return true;
        }
    }

    return false;
}

template<typename T>
inline bool tree_erase_balanced(tree_node<T>*& root, const T& target)
{
    static tree_node<T>* p;
    if (!root)
    {
        return false;
    }

    if (target < root->_item)
    {
        if (root->_left && root->_left->_item == target)
        {
            p = root;
        }
        return tree_erase_balanced(root->_left, target);
    }
    if (target > root->_item)
    {
        if (root->_right && root->_right->_item == target)
        {
            p = root;
        }
        return tree_erase_balanced(root->_right, target);
    }

    if (target == root->_item)
    {
        if (!root->_left)
        {
            if (!root->_right)
            {
                delete root;
                root = NULL;
                return true;
            }
            else
            {
                tree_node<T>* temp = root->_right;
                delete root;
                root = NULL;
                root = temp;
                root->update_height();
                root = rotate(root);
                return true;
            }
        }
        else
        {
            T change;
            tree_remove_max(root->_left, change);
            root->_item = change;
            root->update_height();
            root = rotate(root);
            return true;
        }
    }


    return false;
}

template <typename T>       //erase rightmost node from the tree
                            // store the item in max_value
void tree_remove_max(tree_node<T>*& root, T& max_value)
{
    if (!root->_right)
    {
        if (root->_left)
        {
            max_value = root->_item;
            tree_node<T>* t = root->_left;
            delete root;
            root = NULL;
            root = t;
            root->update_height();
            root = rotate(root);
        }
        else
        {
            max_value = root->_item;
            delete root;
            root = NULL;
        }
    }
    else
    {
        tree_remove_max(root->_right, max_value);
    }
}

template <typename T>       //return copy of tree pointed to by root
tree_node<T>* tree_copy(const tree_node<T>* root)
{
    if (!root)
        return nullptr;

    tree_node<T>* newNode = new tree_node<T>(root->_item);

    newNode->_height = root->_height;

    newNode->_left = tree_copy(root->_left);
    newNode->_right = tree_copy(root->_right);

    return newNode;
}

template <typename T>       //Add tree src to dest
void tree_add(tree_node<T>*& dest, const tree_node<T>* src)
{
    if (!dest)
    {
        return;
    }

    if (!src)
    {
        return;
    }

    tree_insert(dest, src->_item);

    tree_add(dest, src->_left);
    tree_add(dest, src->_right);
}

template <typename T>       // sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int size)
{
    tree_node<T>* root = tree_sorted_list(a, 0, size - 1);
    return root;
}

template<typename T>
tree_node<T>* tree_sorted_list(const T* a, int low, int high)
{
    if (low > high)
        return nullptr;

    int mid = low + (high - low) / 2;

    tree_node<T>* root = new tree_node<T>(a[mid]);

    root->_left = tree_sorted_list(a, low, mid - 1);
    root->_right = tree_sorted_list(a, mid + 1, high);

    root->update_height();
    return root;
}

template<typename T>
inline void tree_to_sorted_list(const tree_node<T>* root, T*& array)
{
    if (!root)
        return;

    tree_to_sorted_list(root->_right, array + 1);
    *array = root->_item;
    tree_to_sorted_list(root->_left, array + 1);
}

template<typename T>
inline void tree_to_sorted_list(const tree_node<T>* root, Vector<T>& v)
{

    if (!root)
        return;
    v.push_back(root->_item);
    tree_to_sorted_list(root->_right, v);
    tree_to_sorted_list(root->_left, v);
}

template<typename T>
inline bool avl_valid(tree_node<T>* root)
{
    if (root) {
        avl_valid(root->_left);
        if (root->balance_factor() > 1 || root->balance_factor() < -1) {
            cout << false << " ";
        }
        else
            cout << true << " ";
        avl_valid(root->_right);
    }
    return true;
}

template<typename T> //This is ment for left heavy | Remember to reset the root
tree_node<T>* rotate_right(tree_node<T>*& root)
{
    tree_node<T>* mid = root->_left;
    root->_left = mid->_right;
    mid->_right = root;

    root->update_height();
    mid->update_height();

    return mid;
}

template<typename T> //This is ment for right heavy | Remember to reset the root
tree_node<T>* rotate_left(tree_node<T>*& root)
{
    tree_node<T>* mid = root->_right;
    root->_right = mid->_left;
    mid->_left = root;

    root->update_height();
    mid->update_height();

    return mid;
}

template<typename T> //Determines What rotation to do, also RECURSION
tree_node<T>* rotate(tree_node<T>*& root)
{
    if (!root)
        return nullptr;

    int Bal = root->balance_factor(), lBal = 0, rBal = 0;

    if (root->_left)
        lBal = root->_left->balance_factor();
    if (root->_right)
        rBal = root->_right->balance_factor();

    //---------------------------------------------
    
    if (Bal > 1 && lBal >= 0)
    {   
        return rotate_right(root);
    }

    //---------------------------------------------

    else if (Bal < -1 && rBal <= 0)
    {
        return rotate_left(root);
    }

    //---------------------------------------------

    else if (Bal > 1 && lBal < 0)
        //RIGHT THEN LEFT CASE
    {
        root->_left = rotate_left(root->_left);
        return rotate_right(root);
    }

    //---------------------------------------------

    else if (Bal < -1 && rBal > 0)
        //LEFT THEN RIGHT CASE
    {  
        root->_right = rotate_right(root->_right);
        return rotate_left(root);
    }

    return root;
}
