#pragma once
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <time.h>
using namespace std;

//--------------------------------------------------------------------------//
//							SORTING FUNCTION CALLS                          //
//--------------------------------------------------------------------------//

template<typename T>
void insertion_sort(T a[], unsigned int size);

template <typename T>
void bubble_sort(T a[], unsigned int size);

template <typename T>
void quick_sort(T a[], unsigned int size);

template <typename T>
void quick_sort(T a[], unsigned int low, unsigned int high);

template <typename T>
int _partition(T a[], unsigned int low, unsigned int high);

template <typename T>
void merge_sort(T a[], unsigned int size);

template <typename T>
void _merge_sort(T a[], unsigned int low, unsigned int mid, unsigned int high);

template <typename T>
void merge_sort(T a[], unsigned int left, unsigned int right);

template <typename T>
void heap_sort(T a[], unsigned int size);

template <typename T>
void _heapify(T a[], unsigned int left, unsigned int right);

//--------------------------------------------------------------------------//
//							TESTING FUNCTION CALLS                          //
//--------------------------------------------------------------------------//

//shuffle elements of a[]
template <typename T>
void shuffle(T a[], unsigned int  size);

template <typename T>
void copy_array(T dest[], const T src[], unsigned int size);

//return true if a[] is in ascending order
template <typename T>
bool verify(const T a[], unsigned int  size);

//return a string "SORTED" or "NOT SORTED" depending if a[] is sorted
template <typename T>
string verifystr(const T a[], unsigned int  size);

//print the array if status_only is true along with info on sortedness of a[]
template <typename T>
void print_array(const T a[], int size, bool status_only = false);

//print a[] from start to end
template <typename T>
void print_array_segment(T a[], unsigned int start, unsigned int end);

//--------------------------------------------------------------------------//
//				   	    SORTING FUNCTION DEFINITIONS                        //
//--------------------------------------------------------------------------//

template<typename T>
inline void insertion_sort(T a[], unsigned int size)
{
	for (int i = 1; i < size; i++)
	{
		T base = a[i];
		int pos = i - 1;
		while (pos >= 0 && base <= a[pos])
		{
			a[pos + 1] = a[pos];
			pos -= 1;
		}
		a[pos + 1] = base;
	}
}

template<typename T>
inline void bubble_sort(T a[], unsigned int size)
{
	bool swapped;
	for (int i = 0; i < size - 1; i++)
	{
		swapped = false;
		for (int j = 0; j < size - i - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
				swapped = true;
			}
		}

		if (!swapped)
			break;
	}
}

template<typename T>
inline void quick_sort(T a[], unsigned int size)
{
	quick_sort(a, 0, size - 1);
}

template<typename T>
inline void quick_sort(T a[], unsigned int low, unsigned int high)
{
	int piv;
	if (low < high)
	{
		piv = _partition(a, low, high);

		quick_sort(a, low, piv - 1);
		quick_sort(a, piv + 1, high);
	}
}

template<typename T>
inline int _partition(T a[], unsigned int low, unsigned int high)
{
	int pivot = low; 
	T pivot_element = a[low];

	for (int i = low + 1; i <= high; i++)
	{
		if (a[i] <= pivot_element)
		{
			pivot++;
			swap(a[i], a[pivot]);
		}
	}

	swap(a[pivot], a[low]);

	return pivot;
}

template<typename T>
inline void merge_sort(T a[], unsigned int size)
{
	merge_sort(a, 0, size - 1);
}

template<typename T>
inline void _merge_sort(T a[], unsigned int low, unsigned int mid, unsigned int high)
{
	int n1 = mid - low + 1;
	int n2 = high - mid;
	T* L = new T[n1];
	T* R = new T[n2];

	for (int i = 0; i < n1; i++)
	{
		L[i] = a[low + i];
	}
	for (int i = 0; i < n2; i++)
	{
		R[i] = a[mid + 1 + i];
	}

	int i = 0;
	int j = 0;
	int k = low;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			a[k] = L[i];
			i++;
		}
		else
		{
			a[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1)
	{
		a[k] = L[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		a[k] = R[j];
		j++;
		k++;
	}

	delete L;
	delete R;
}

template<typename T>
inline void merge_sort(T a[], unsigned int left, unsigned int right)
{
	if (left < right)
	{
		int m = left + (right - left) / 2;
		merge_sort(a, left, m);
		merge_sort(a, m + 1, right);
		_merge_sort(a, left, m, right);
	}
}

template<typename T>
inline void heap_sort(T a[], unsigned int size) //Wrong!
{
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		_heapify(a, size, i);
	}

	for (int i = size - 1; i > 0; i--)
	{
		swap(a[0], a[i]);
		_heapify(a, i, 0);
	}
}

template<typename T>
inline void _heapify(T a[], unsigned int size, unsigned int root)
{
	int high = root;
	int subL = 2 * root + 1;
	int subR = 2 * root + 2;

	if (subL < size && a[subL] > a[high])
		high = subL;

	if (subR < size && a[subR] > a[high])
		high = subR;

	if (high != root)
	{
		swap(a[root], a[high]);
		_heapify(a, size, high);
	}
}

//--------------------------------------------------------------------------//
//				   	    TESTING FUNCTION DEFINITIONS                        //
//--------------------------------------------------------------------------//

template<typename T>
inline void shuffle(T a[], unsigned int size)
{
	srand(time(0));
	int c = 0, b = 0;
	for (int i = 0; i < 100; i++)
	{
		c = rand() % size;
		b = rand() % size;
		if (c != b)
			swap(a[c], a[b]);
	}
}

template<typename T>
inline void copy_array(T dest[], const T src[], unsigned int size)
{
	dest = new T[size];
	for (int i = 0; i < size; i++)
	{
		dest[i] = src[i];
	}
}

template<typename T>
inline bool verify(const T a[], unsigned int size)
{
	for (int i = 1; i < size; i++)
	{
		T base = a[i];
		int pos = i - 1;
		if (a[pos] > base)
			return false;
	}
	return true;
}

template<typename T>
inline string verifystr(const T a[], unsigned int size)
{
	if (verify(a, size))
		return string("SORTED");
	else
		return string("NOT SORTED");
}

template<typename T>
inline void print_array(const T a[], int size, bool status_only)
{
	if (status_only)
		cout << verifystr(a, size) << "| ";

	for (int i = 0; i < size; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;

}

template<typename T>
inline void print_array_segment(T a[], unsigned int start, unsigned int end)
{
	for (int i = start; i < end; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
}
