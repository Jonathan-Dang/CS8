/* Author: Jonathan Dang
*  Project: AVL
*  Purpose: Balanced BST
*/
#include <iostream>
#include "../BST Functions and Class/BST.h"
#include "AVL.h"
using namespace std;

void test_rotates();
void test_AVL();

int main()
{
	cout << "========================================================\n";
	test_rotates();
	cout << "--------------------------------------------------------\n";
	cout << "STARTING ARRAY SPECIFIC ERASING TESTING\n";
	int arr[] = { 22,30,33,43,45,56,62,77,82,85,92,94,95 };
	AVL<int> avl(arr, 13);
	cout << avl << endl;
	avl.erase(92);
	cout << "--------------------------------------------------------\n";
	cout << avl << endl;
	cout << "ENDING ERASING ARRAY TESTING\n";
	cout << "--------------------------------------------------------\n";
	test_AVL();
	cout << "=============================END========================\n";
	return 0;
}

void test_rotates()
{
	cout << "BEGINING ROTATION TESTING\n";
	tree_node<int>* t = nullptr;
	for (int i = 0; i < 3; i++)
	{
		tree_insert(t, i);
	}
	tree_print(t);

	t = rotate(t);
	cout << endl << "-------------------" << endl;

	tree_print(t);
	cout << "COMPLETED ROTATION TESTING\n";
}

void test_AVL()
{
	char input;

	AVL<int> Tree;

	cout << Tree;

	cout << "[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it: \n";
	cin >> input;
	while (tolower(input) != 'x')
	{
		char translate = tolower(input);
		switch (translate)
		{
		case('r'):
		{
			int insert = rand() % 1000;
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
		case('c'):
		{
			Tree.clear();
			break;
		}
		case('s'):
		{
			int input = 0;
			tree_node<int>* temp;
			cout << "Please Enter a number to Search: ";
			cin >> input;
			if (Tree.search(input, temp))
			{
				cout << "FOUND!\n Input found at Height: " << temp->height() << endl;
				cout << "Value: " << temp->_item << endl;
			}
			else
			{
				cout << "NOT FOUND!\n Input does not exist in tree!\n";
			}
			break;
		}
		case('e'):
		{
			int input = 0;
			cout << "Please Enter a number to Erase: ";
			cin >> input;
			Tree.erase(input);
			break;
		}
		}
		cout << Tree;
		cout << "[R]andom  [I]nsert  [C]clear  [S]earch  [E]rase      e[X]it: \n";
		cin >> input;
	}
}