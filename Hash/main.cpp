/* Author: Jonathan Dang
*  Project: Hash
*  Purpose: Data Structure
*/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include "DHash.h"
#include "CHash.h"
using namespace std;

void test_dhash();
void test_interactive_dhash();

void test_chash();
void test_interactive_chash();

int main()
{
	cout << "==========================================================\n";
	const bool DhashAuto = false;
	const bool DhashInteractive = false;
	const bool ChashAuto = true;
	const bool ChashInteractive = true;

	if (DhashAuto)
	{
		cout << "==============Double Hash Random Testing==============\n";
		test_dhash();
	}

	if (ChashAuto)
	{
		cout << "===============Chain Hash Random Testing==============\n";
		test_chash();
	}

	if (DhashInteractive)
	{
		cout << "================Double Hash Interactive===============\n";
		test_interactive_dhash();
	}

	if (ChashInteractive)
	{
		cout << "=================Chain Hash Interactive===============\n";
		test_interactive_chash();
	}
	cout << "============================END===========================\n";
	return 0;
}
	
void test_dhash()
{
	DHash<int> dh(20);
	cout << "Filling hash until full\n";
	for (int i = 0; i < 20; i++)
	{
		dh.insert(record<int>(i, 10));
	}
	cout << dh << endl;
	cout << "Attempting to Add into a full hash\n";
	dh.insert(record<int>(100, 1000));
	cout << dh << endl;
	cout << "Deleting the entire hash\n";
	for (int i = 0; i < 20; i++)
	{
		dh.remove(i);
	}
	cout << dh << endl;
	cout << "Attempting to remove from an empty hash\n";
	dh.remove(10);
	cout << dh << endl;
	cout << "Inserting into one spot, forcing collisions\n";
	for (int i = 0; i < 20; i++)
	{
		dh.insert(record<int>(10 * (2 * i), i * 100));
	}
	cout << "Collisions:" << dh.collision() << endl;
	cout << dh << endl;
	cout << "Searching for a record\n";
	record<int> temp;
	if (dh.search(0, temp))
	{
		cout << "SUCCESS: " << temp << endl;
	}
	else
		cout << "FAILED!\n";
	cout << "Removing all of the stored records one by one\n";
	for (int i = 0; i < 20; i++)
	{
		dh.remove(10 * (2 * i));
		cout << dh << endl;
	}

	cout << "FULL RANDOM TESTING, CHECKING COLLISIONS AND SIZE!\n";
	srand(time(NULL));
	DHash<int> r;
	for (int i = 0; i < 811; i++)
	{
		r.insert(record<int>(rand() % 1000, rand() % 1000));
		r.insert(record<int>(rand() % 1000, rand() % 1000));
	}
	cout << "Collisions: " << r.collision() << endl
		<< "Size: " << r.size() << endl
		<< "Capacity: " << r.capacity() << endl;
}

void test_interactive_dhash()
{
	char input;
	srand(time(0));
	DHash<int> dh(20);

	do {
		cout << "[S]ize() [I]nsert [R]andom [D]elete [F]ind value [?]exists?   e[X]it : ";
		cin >> input;
		switch (tolower(input))
		{
		case('s'):
		{
			cout << "Size: " << dh.size() << endl;
			break;
		}
		case('i'):
		{
			record<int> temp;
			cout << "(IE key:value) Input: ";
			cin >> temp;
			dh.insert(temp);
			cout << "INSERTED: " << temp << endl;
			break;
		}
		case('r'):
		{
			record<int> temp(record<int>(rand() % 1000, rand() % 1000));
			dh.insert(temp);
			cout << "INSERTED: " << temp << endl;
			break;
		}
		case('d'):
		{
			int temp;
			cout << "Key: ";
			cin >> temp;
			dh.remove(temp);
			break;
		}
		case('f'):
		{
			cout << "Key: ";
			int temp;
			record<int> r;
			cin >> temp;
			if (dh.search(temp, r))
			{
				cout << "FOUND!\n";
				cout << r << endl;
			}
			else
				cout << "FAILED!\n";
			break;
		}
		case('?'):
		{
			int temp;
			cout << "Key: ";
			cin >> temp;
			if (dh.is_present(temp))
				cout << "Exists!\n";
			else
				cout << "Doesn't Exist!\n";
			break;
		}
		default:
			break;
		}
		cout << dh << endl;
	} while (tolower(input) != 'x');
}

void test_chash()
{
	CHash<int> dh(20);
	cout << "Filling hash until full\n";
	for (int i = 0; i < 20; i++)
	{
		dh.insert(record<int>(i, 10));
	}
	cout << dh << endl;
	cout << "Attempting to Add into a full hash\n";
	dh.insert(record<int>(100, 1000));
	cout << dh << endl;
	cout << "Deleting the entire hash\n";
	for (int i = 0; i < 20; i++)
	{
		dh.remove(i);
	}
	dh.remove(100);
	cout << dh << endl;
	cout << "Attempting to remove from an empty hash\n";
	dh.remove(10);
	cout << dh << endl;
	cout << "Inserting into one spot, forcing collisions\n";
	for (int i = 0; i < 5; i++)
	{
		dh.insert(record<int>(10 * (2 * i), i * 100));
	}
	cout << "Collisions:" << dh.collision() << endl;
	cout << dh << endl;
	cout << "Searching for a record\n";
	record<int> temp;
	if (dh.search(0, temp))
	{
		cout << "SUCCESS: " << temp << endl;
	}
	else
		cout << "FAILED!\n";
	cout << "Removing all of the stored records one by one\n";
	for (int i = 0; i < 5; i++)
	{
		dh.remove(10 * (2 * i));
		cout << dh << endl;
	}

	cout << "FULL RANDOM TESTING, CHECKING COLLISIONS AND SIZE!\n";
	srand(time(NULL));
	DHash<int> r;
	for (int i = 0; i < 811; i++)
	{
		r.insert(record<int>(rand() % 1000, rand() % 1000));
		r.insert(record<int>(rand() % 1000, rand() % 1000));
	}
	cout << "Collisions: " << r.collision() << endl
		<< "Size: " << r.size() << endl
		<< "Capacity: " << r.capacity() << endl;
}

void test_interactive_chash()
{
	char input;
	srand(time(0));
	CHash<int> dh(20);

	do {
		cout << "[S]ize() [I]nsert [R]andom [D]elete [F]ind value [?]exists?   e[X]it : ";
		cin >> input;
		switch (tolower(input))
		{
		case('s'):
		{
			cout << "Size: " << dh.size() << endl;
			break;
		}
		case('i'):
		{
			record<int> temp;
			cout << "(IE key:value) Input: ";
			cin >> temp;
			dh.insert(temp);
			cout << "INSERTED: " << temp << endl;
			break;
		}
		case('r'):
		{
			record<int> temp(record<int>(rand() % 1000, rand() % 1000));
			dh.insert(temp);
			cout << "INSERTED: " << temp << endl;
			break;
		}
		case('d'):
		{
			int temp;
			cout << "Key: ";
			cin >> temp;
			dh.remove(temp);
			cout << "REMOVED: " << temp << endl;
			break;
		}
		case('f'):
		{
			cout << "Key: ";
			int temp;
			record<int> r;
			cin >> temp;
			if (dh.search(temp, r))
			{
				cout << "FOUND!\n";
				cout << r << endl;
			}
			else
				cout << "FAILED!\n";
			break;
		}
		case('?'):
		{
			int temp;
			cout << "Key: ";
			cin >> temp;
			if (dh.is_present(temp))
				cout << "Exists!\n";
			else
				cout << "Doesn't Exist!\n";
			break;
		}
		default:
			break;
		}
		cout << dh << endl;
	} while (tolower(input) != 'x');
}
