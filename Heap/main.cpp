/* Author: Jonathan Dang
*  Project: Heap
*  Purpose: Yes
*/
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include "PQueue.h"
using namespace std;

void test_heap();

void test_pq();

int main()
{
	cout << "===========================================================\n";
	//test_heap();
	//cout << "-----------------------------------------------------------\n";
	//test_pq();
	cout << "==============================END==========================\n";
	return 0;
}

void test_heap()
{
	cout << "PREVIEW TO HEAP\n";
	Heap<int> h;
	h.insert(10);
	h.insert(15);
	h.insert(17);
	h.insert(8);
	h.insert(13);
	h.insert(14);
	h.insert(25);
	cout << h << endl;

	cout << "===========================================================\n";

	char input;

	Heap<int> Tree;

	cout << Tree;

	cout << "[R]andom  [I]nsert  [P]op     e[X]it: \n";
	cin >> input;
	while (tolower(input) != 'x')
	{
		char translate = tolower(input);
		switch (translate)
		{
		case('r'):
		{
			int insert = rand() % 100;
			cout << "Inserting " << insert << endl;
			Tree.insert(insert);
			break;
		}
		case('i'):
		{
			int input = 0;
			cout << "Please enter a number to Insert: ";
			cin >> input;
			Tree.insert(input);
			break;
		}
		case('p'):
		{
			cout << "POPED: " << Tree.Pop() << endl;
			break;
		}
		default:
			break;
		}
		cout << Tree;
		cout << "[R]andom  [I]nsert  [P]op     e[X]it: \n";
		cin >> input;
	}
}

void test_pq()
{
	PQueue<int> pq;
	for (int i = 0; i < 100; i++) {
		pq.insert(rand() % 1000 + 1, rand() % 10 + 1, rand() % 10000);
	}


	cout << setw(5) << "Num" << "|"
		<< setw(10) << "Item"
		<< setw(11) << "Priority"
		<< setw(18) << "Serial Number" << endl;

	for (int i = 1; i < 101; i++)
	{
		info<int> temp = pq.Pop();
		cout << setw(5) << i << "|" 
			<< setw(10) << temp._item 
			<< setw(10) << temp._priority 
			<< setw(10) << temp._serial_number << endl;
	}
}

