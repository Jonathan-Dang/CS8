/*Author: Jonathan Dang
* Project: Sorting
* Purpose: Sorting...
*/
#include <iostream>
#include "Sorting.h"
#include "Timer.h"
using namespace std;

void average_run_time(void (*f)(int*, unsigned int), unsigned int size
	, unsigned int runs);

int main()
{
	cout << "=============================================================\n";
	cout << "Insertion Sort\n";
	average_run_time(insertion_sort<int>, 50000, 500);
	cout << "Bubble Sort\n";
	average_run_time(bubble_sort<int>, 50000, 500);
	cout << "Quick Sort\n";
	average_run_time(quick_sort<int>, 50000, 500);
	cout << "Merge Sort\n";
	average_run_time(merge_sort<int>, 50000, 500);
	cout << "Heap Sort\n";
	average_run_time(heap_sort<int>, 50000, 500);
	cout << "===============================END===========================\n";
	return 0;
}

void average_run_time(void(*f)(int*, unsigned int), unsigned int size,
	unsigned int runs)
{
	srand(time(NULL));
	Vector<double> v;
	int* a = new int[size];

	for (int i = 0; i < size; i++)
	{
		a[i] = rand() % 100;
	}

	for (int i = 0; i < runs; i++)
	{
		shuffle(a, size);
		double d = time_sort_routine(a, size, f);
		v.push_back(d);
	}

	double average = 0;
	double aver_size = v.size();
	for (int i = 0; i < aver_size; i++)
	{
		average += v.pop_back();
	}
	average /= aver_size;

	cout << "Average Run Time: " << average << endl;
}
