#pragma once
#include "BST_FUNCTIONS.h"
#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
class BST {
public:
	BST();
	BST(const T* sorted_list, int size = -1);

	//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	BST(const BST<T>& copy_me);
	BST<T>& operator =(const BST<T>& rhs);
	~BST();

	//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	void insert(const T& insert_me);
	void erase(const T& target);
	bool search(const T& target, tree_node<T>*& found_ptr);

	friend ostream& operator <<(ostream& outs, const BST<T>& tree)
	{
		tree_print(tree.root, 0, outs);
		return outs;
	}
	BST<T>& operator +=(const BST<T>& rhs);
private:
	tree_node<T>* root;
};


template <typename T>
inline BST<T>::BST()
{
	root = nullptr;
}

template <typename T>
inline BST<T>::BST(const T* sorted_list, int size)
{
	assert(size > 0);
	root = tree_from_sorted_list(sorted_list, size);
}

template <typename T>
inline BST<T>::BST(const BST<T>& copy_me)
{
	root = tree_copy(copy_me.root);
}

template <typename T>
inline BST<T>& BST<T>::operator=(const BST<T>& rhs)
{
	if (&this == &rhs) { return *this; }
	tree_clear(root);
	root = tree_copy(rhs.root);
	return *this;
}

template <typename T>
inline BST<T>::~BST()
{
	tree_clear(root);
	root = nullptr;
}

template <typename T>
inline void BST<T>::insert(const T& insert_me)
{
	tree_insert(root, insert_me);
}

template <typename T>
inline void BST<T>::erase(const T& target)
{
	tree_erase(root, target);
}

template <typename T>
inline bool BST<T>::search(const T& target, tree_node<T>*& found_ptr)
{
	return tree_search(root, target, found_ptr);
}

template <typename T>
inline BST<T>& BST<T>::operator+=(const BST<T>& rhs)
{
	tree_add(root, rhs.root);
	return *this;
}
