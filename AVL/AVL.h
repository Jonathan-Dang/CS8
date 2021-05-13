#pragma once
#include "../BST Functions and Class/BST.h"
#include "../Vector/Vector.h"
#include <cassert>

template <typename T>
class AVL {
public:
	AVL();
	AVL(const T* sorted_list, int size = -1);

	//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	AVL(const AVL<T>& copy_me);
	AVL<T>& operator =(const AVL<T>& rhs);
	~AVL();

	//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

	T top();
	T pop();
	void vectorized(Vector<T>& v);
	bool isEmpty();
	void insert(const T& insert_me);
	bool erase(const T& target);
	void clear();
	bool search(const T& target, tree_node<T>*& found_ptr);
	bool isValid();

	friend ostream& operator <<(ostream& outs, const AVL<T>& tree)
	{
		tree_print(tree.root,0,outs);
		return outs;
	}
	AVL<T>& operator +=(const AVL<T>& rhs);
private:
	tree_node<T>* root;
};

template<typename T>
inline AVL<T>::AVL()
{
	root = nullptr;
}

template<typename T>
inline AVL<T>::AVL(const T* sorted_list, int size)
{
	assert(size > 0);
	root = tree_from_sorted_list(sorted_list, size);
}

template<typename T>
inline AVL<T>::AVL(const AVL<T>& copy_me): root(tree_copy(copy_me.root))
{
	//Left Empty
}

template<typename T>
inline AVL<T>& AVL<T>::operator=(const AVL<T>& rhs)
{
	tree_clear(root);
	root = tree_copy(rhs.root);
	return *this;
}

template<typename T>
inline AVL<T>::~AVL()
{
	tree_clear(root);
	root = nullptr;
}

template<typename T>
inline T AVL<T>::top()
{
	return root->_item;
}

template<typename T>
inline T AVL<T>::pop()
{
	T hold;
	tree_remove_max(root, hold);
	return hold;
}

template<typename T>
inline void AVL<T>::vectorized(Vector<T>& v)
{
	tree_to_sorted_list(root, v);
}

template<typename T>
inline bool AVL<T>::isEmpty()
{
	return root;
}

template<typename T>
inline void AVL<T>::insert(const T& insert_me)
{
	tree_insert_balanced(root, insert_me);
	root = rotate(root);
	/*isValid();
	cout << endl;*/
}

template<typename T>
inline bool AVL<T>::erase(const T& target)
{
	bool r = tree_erase_balanced(root, target);
	root = rotate(root);
	/*isValid();
	cout << endl;*/
	return r;
}

template<typename T>
inline void AVL<T>::clear()
{
	tree_clear(root);
	root = nullptr;
}

template<typename T>
inline bool AVL<T>::search(const T& target, tree_node<T>*& found_ptr)
{
	return tree_search(root, target, found_ptr);
}

template<typename T>
inline bool AVL<T>::isValid()
{
	return avl_valid(root);
}

template<typename T>
inline AVL<T>& AVL<T>::operator+=(const AVL<T>& rhs)
{
	tree_add(root, rhs.root);
	root = rotate(root);
	return *this;
}
