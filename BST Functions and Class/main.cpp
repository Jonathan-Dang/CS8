/*Author: Jonathan Dang
* Project: BST Functions and Class
* Purpose: Trees and Data Structure
*/
#include <iostream>
#include <cstdlib>
#include "BST.h"
using namespace std;

void test_tree_node();
void test_BST();

int main()
{
	cout << "================================================\n";
	cout << "BEGIN TREE NODE FUNCTION TESTS!~\n";
	test_tree_node();
	cout << "END OF TREE NODE FUNCTION TESTS!\n";
	cout << "================================================\n";
	cout << "BEGIN TREE CLASS TESTING!\n";
	test_BST();
	cout << "END OF TREE CLASS TESTING!\n";
	cout << "=========================END====================\n";
	return 0;
}

void test_tree_node()
{
	tree_node<int>* t = nullptr;
	int array[10] = { 4, 5, 9,-20,30,1,20,4,6,9 };
	for (int i = 0; i < 10; i++)
	{
		tree_insert(t, array[i]);
	}
	cout << "Initialized tree noded\n";
	tree_print(t);

	cout << "Searching for number 1!\n";
	tree_node<int>* temp = nullptr;
	temp = tree_search(t, 1);
	cout << "FOUND: " << *temp << endl;

	cout << "Searching for -50!\n";
	temp = tree_search(t, -50);
	cout << "FOUND: " << temp << endl;
	cout << "if 0, then its not in the tree!\n";

	cout << "Removing the right most leaf node!\n";
	int hold = 0;
	tree_remove_max(t, hold);
	cout << "MAX VALUE: " << hold << "|" << endl;
	tree_print(t);

	cout << "Removing number 20!\n";
	if (tree_erase(t, 20))
	{
		cout << "SUCCESS!\n";
		tree_print(t);
	}
	else
	{
		cout << "FAIL!\n";
		tree_print(t);
	}

	cout << "Removing number 20!\n";
	if (tree_erase(t, 20))
	{
		cout << "SUCCESS!\n";
		tree_print(t);
	}
	else
	{
		cout << "FAIL!\n";
		tree_print(t);
	}

	cout << "Copying t to temp!\n";
	temp = tree_copy(t);
	cout << "This is T\n"
		<< "================================\n";
	tree_print(t);
	cout << "===============================\n";
	cout << "This is Temp\n"
		<< "================================\n";
	tree_print(temp);
	cout << "================================\n";

	cout << "Tree_ADD function!\n";
	tree_add(t, temp);
	cout << "NEW T:\n"
		<< "================================\n";
	tree_print(t);
	cout << "================================\n";

	cout << "CLEARING BOTH TREES!\n";
	tree_clear(t);
	tree_clear(temp);
	cout << "This is T\n"
		<< "================================\n";
	tree_print(t);
	cout << "===============================\n";
	cout << "This is Temp\n"
		<< "================================\n";
	tree_print(temp);
	cout << "================================\n";

	t = new tree_node<int>;
	int arrayL[10];
	for (int i = 0; i < 10; i++)
	{
		arrayL[i] = i;
	}
	t = tree_from_sorted_list(arrayL, 10);
	cout << "TREE FROM SORTED LIST!\n";
	tree_print(t);

	cout << endl << "END OF TESTING\n";
}

void test_BST()
{
	char input;

	BST<int> Tree;

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
			Tree.insert(rand() % 100);
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
			Tree.~BST();
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
