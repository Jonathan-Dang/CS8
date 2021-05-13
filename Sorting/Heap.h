#pragma once
#include <iostream>
#include "Vector.h"
#include <utility>
#include <iomanip>
using namespace std;

template <typename T>
class Heap
{
public:
	//Constructors
	Heap();
	Heap(Vector<T> v);

	//Main Heap Functions
	void insert(const T& insert_me);
	T Pop();

	//External Heap Functions
	bool is_empty() const;
	int size() const;
	int capacity() const;
	friend ostream& operator << (ostream& outs, const Heap<T>& print_me)
	{
		outs << "-----------------------------------------------------\n";
		print_me.print_tree(outs);
		outs << endl;
		outs << "-----------------------------------------------------\n";
		print_me.print_tree(0);
		return outs;
	}

private:
	Vector<T> _tree;

	void print_tree(ostream& outs = cout) const; //Print it like an array
	void print_tree(unsigned int root, int level = 0, ostream& outs = cout) const; //Print it like a tree


	bool is_leaf(int i) const; //Check if index has no children
	unsigned int parent_index(unsigned int i) const; //Gives Previous Root's Index, IE the parent of current
	unsigned int left_child_index(unsigned int i)const; //Gives Index of current space's left child.
	unsigned int right_child_index(unsigned int i) const; //Gives Same thing as above but right child.
	unsigned int big_child_index(unsigned int i) const;	//Gives Bigest Child's Index ?
	void swap_with_parent(unsigned int i); //Index is child, so swap with parent

	void heap_up(unsigned int i); // Ment for Inputing
	void heap_down(unsigned int i); // Ment for erasing/poping in this case
};

template<typename T>
inline void Heap<T>::print_tree(ostream& outs) const
{
	for (int i = 0; i < _tree.size(); i++)
	{
		outs << "|" << _tree[i] << "| ";
	} //For Loop
}

template<typename T>
inline void Heap<T>::print_tree(unsigned int root, int level, ostream& outs) const
{
	if (root >= size())
		return;

	print_tree(right_child_index(root), level + 1, outs);
	outs << endl << setw(level * 3) << "[" << _tree[root] << "]" << endl;
	print_tree(left_child_index(root), level + 1, outs);
}

template<typename T>
inline bool Heap<T>::is_leaf(int i) const
{
	return (i >= (size() / 2)) && (i < size());
}

template<typename T>
inline unsigned int Heap<T>::parent_index(unsigned int i) const
{
	return (i - 1) / 2;
}

template<typename T>
inline unsigned int Heap<T>::left_child_index(unsigned int i) const
{
	return (2 * i) + 1;
}

template<typename T>
inline unsigned int Heap<T>::right_child_index(unsigned int i) const
{
	return (2 * i) + 2;
}

template<typename T>
inline unsigned int Heap<T>::big_child_index(unsigned int i) const
{
	unsigned int big = i, left = left_child_index(i),
		right = right_child_index(i);

	if (left < size() || right < size())
	{
		if (_tree[left] > _tree[big])
			big = left;

		if(_tree[right] > _tree[big])
			big = right;
	}// Checks within size
	return big;
}

template<typename T>
inline void Heap<T>::swap_with_parent(unsigned int i)
{
	swap(_tree[i], _tree[parent_index(i)]);
}

template<typename T>
inline void Heap<T>::heap_up(unsigned int i)
{
	//Boundaries: [0,size()]
	//continue only if parent is smaller
	unsigned int parent = parent_index(i);

	if (parent >= 0 && parent < size())
	{
		if (_tree[i] > _tree[parent])
		{
			swap_with_parent(i);
			heap_up(parent);
		}
	}
}

template<typename T>
inline void Heap<T>::heap_down(unsigned int i)
{
	if (is_leaf(i))
		return;

	if (big_child_index(i) != i)
	{
		unsigned int pos = big_child_index(i);
		swap_with_parent(pos);
		heap_down(pos);
	}
}

template<typename T>
inline Heap<T>::Heap()
{
}

template<typename T>
inline Heap<T>::Heap(Vector<T> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		insert(v[i]);
	}
}

template<typename T>
inline void Heap<T>::insert(const T& insert_me)
{
	_tree.push_back(insert_me);

	if (size() > 0)
	{
		heap_up(size() - 1);
	}
}

template<typename T>
inline T Heap<T>::Pop()
{

	T hold = _tree[0];
	_tree[0] = _tree.back();
	_tree.pop_back();

	if (size() > 0)
		heap_down(0);

	return hold;
}

template<typename T>
inline bool Heap<T>::is_empty() const
{
	return _tree.empty();
}

template<typename T>
inline int Heap<T>::size() const
{
	return _tree.size();
}

template<typename T>
inline int Heap<T>::capacity() const
{
	return _tree.capacity();
}

