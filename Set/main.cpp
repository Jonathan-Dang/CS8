/* Author: Jonathan Dang
*  Project: Lab 4, Set
*  Purpose: I am not too sure but Data Structure
*/
#include <iostream>
#include "Set.h"
using namespace std;

int main()
{
	cout << "=============================================================\n";
	Set<int> a, b;
	for (int i = 0; i < 10; i++)
	{
		a.insert(i);
	}
	for (int i = 5; i < 15; i++)
	{
		b.insert(i);
	}
	Set<int> c;
	a.Intersection(b, c);
	cout << "BASE TREE\n";
	cout << a << endl;
	cout << "Intersecting Tree / Union Tree\n";
	cout << b << endl;
	cout << "INTERSECTION TREE\n";
	cout << c << endl;
	cout << "UNION TREE\n";
	a.Union(b, c);
	cout << c << endl;
	cout << "===============================END===========================\n";
	return 0;
}