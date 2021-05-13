/*Author: Jonathan Dang
* Project: BTree and BTree Accessories
* Purpose: Data Structure
*/
#include <iostream>
#include "BTree.h"
#include <string.h>
using namespace std;

void test_BTree_functions();

void test_BTree();

void test_BTree_string();

int main()
{
	cout << "=============================================================\n";
	//test_BTree_functions();
	//cout << "---------------------END OF BTREE FUNCTION TESTS-------------\n";
	test_BTree();
	cout << "===============================END===========================\n";
	return 0;
}

void test_BTree_functions()
{
	int a[10] = { 1,2,3,4,5 };
	int aSize = 5;
	int b[5] = { 6,7,8,9,10 };
	int bSize = 5;

	cout << "Array a: "; 
	print_array(a, aSize, 0);
	cout << endl;
	cout << "Array b: ";
	print_array(b, bSize, 0);
	cout << endl;

	cout << "Maximal of a[0] and b[0]: " << maximal(a[0], b[0]) << endl;

	cout << "Index of maximal a[0]: " << index_of_maximal(&a[0], aSize) << endl;

	cout << "Ordered insert into a\n";
	ordered_insert(a, aSize, 2);
	cout << "Array a: ";
	print_array(a, aSize, 0);
	cout << endl;

	cout << "First Greater 4 pos: " << first_ge(a, aSize, 4) << endl;

	cout << "Attach Item 7\n";
	attach_item(a, aSize, 7);
	cout << "Array a: ";
	print_array(a, aSize, 0);
	cout << endl;

	cout << "Detach Item 7\n";
	int toss;
	detach_item(a, aSize, toss);
	cout << "Array a: ";
	print_array(a, aSize, 0);
	cout << endl;
	cout << "Tossed: " << toss << endl;

	cout << "Insert item 10 at pos 3\n";
	insert_item(a, 2, aSize, 10);
	cout << "Array a: ";
	print_array(a, aSize, 0);
	cout << endl;
	
	cout << "Delete item 10 from pos 3\n";
	delete_item(a, 2, aSize, toss);
	cout << "Array a: ";
	print_array(a, aSize, 0);
	cout << endl;
	cout << "Tossed: " << toss << endl;

	cout << "Copying array b to array a\n";
	cout << "Array a: ";
	print_array(a, aSize, 0);
	cout << endl;
	cout << "Array b: ";
	print_array(b, bSize, 0);
	cout << endl;
	copy_array(a, b, aSize, bSize);
	cout << "---------------------------------------\n";
	cout << "Array a: ";
	print_array(a, aSize, 0);
	cout << endl;
	cout << "Array b: ";
	print_array(b, bSize, 0);
	cout << endl;

	cout << "Merging\n";
	cout << "Array a: ";
	print_array(a, aSize, 0);
	cout << endl;
	cout << "Array b: ";
	print_array(b, bSize, 0);
	cout << endl;
	merge(a, aSize, b, bSize);
	cout << "-----------------------------------------\n";
	cout << "Array a: ";
	print_array(a, aSize, 0);
	cout << endl;
	cout << "Array b: ";
	print_array(b, bSize, 0);
	cout << endl;

	cout << "Spliting\n";
	cout << "Array a: ";
	print_array(a, aSize, 0);
	cout << endl;
	cout << "Array b: ";
	print_array(b, bSize, 0);
	cout << endl;
	split(a, aSize, b, bSize);
	cout << "------------------------------------------\n";
	cout << "Array a: ";
	print_array(a, aSize, 0);
	cout << endl;
	cout << "Array b: ";
	print_array(b, bSize, 0);
	cout << endl;
}

void test_BTree()
{
	char input;
	bool dup = false;
	cout << "Do you want to allow dups?\n";
	cin >> input;
	if (tolower(input) == 'y')
		dup = true;
	else if (tolower(input) == 'n')
		dup = false;

	BTree<int> bt(dup);
	input = '\n';

	do
	{
		cout << bt << endl;
		cout << "[I]nput [D]elete [R]andom [C]ontains C[L]ear List [S]ize e[X]it \n";
		cin >> input;

		switch (tolower(input))
		{
		case('i'):
		{
			cout << "Input Value: ";
			int temp = 0;
			cin >> temp;
			bt.insert(temp);
			break;
		}//Case i
		case('d'):
		{
			cout << "Delete Value: ";
			int temp = 0;
			cin >> temp;
			bt.remove(temp);
			break;
		}//Case d
		case('r'):
		{
			int temp = rand() % 1000;
			cout << "Inserted: " << temp << endl;
			bt.insert(temp);
			break;
		}//Case r
		case('c'):
		{
			cout << "Search Value: ";
			int temp = 0;
			cin >> temp;
			if (bt.contains(temp))
				cout << "Value " << temp << " is in the tree!\n";
			else
				cout << "Value " << temp << " is NOT in the tree!\n";
			break;
		}//Case c
		case('l'):
		{
			bt.clear_tree();
			break;
		}//Case l
		case('s'):
		{
			cout << "Size: " << bt.size() << endl;
			break;
		}//Case s
		}
	} while (tolower(input) != 'x');
}

void test_BTree_string()
{
	char input;
	bool dup = false;
	cout << "Do you want to allow dups?\n";
	cin >> input;
	if (tolower(input) == 'y')
		dup = true;
	else if (tolower(input) == 'n')
		dup = false;

	BTree<string> bt;
	input = '\n';
	do
	{
		cout << bt << endl;
		cout << "[I]nput [D]elete [C]ontains C[L]ear List [S]ize e[X]it \n";
		cin >> input;
		switch (tolower(input))
		{
		case('i'):
		{
			cout << "Input Value: ";
			string temp;
			cin >> temp;
			bt.insert(temp);
			break;
		}//Case i
		case('d'):
		{
			cout << "Delete Value: ";
			string temp;
			cin >> temp;
			bt.remove(temp);
			break;
		}//Case d
		case('c'):
		{
			cout << "Search Value: ";
			string temp;
			cin >> temp;
			if (bt.contains(temp))
				cout << "Value " << temp << " is in the tree!\n";
			else
				cout << "Value " << temp << " is NOT in the tree!\n";
			break;
		}//Case c
		case('l'):
		{
			bt.clear_tree();
			break;
		}//Case l
		case('s'):
		{
			cout << "Size: " << bt.size() << endl;
			break;
		}//Case s
		}
	} while (tolower(input) != 'x');

}
