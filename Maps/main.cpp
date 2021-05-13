/* Author: Jonathan Dang
*  Project: Maps
*  Purpose: Data Structures
*/
#include <iostream>
#include "Map.h"
#include "MultiMap.h"
#include <string.h>
using namespace std;

int main()
{
	cout << "=============================================================\n";
	MultiMap<string, string> m;
	//m.insert("John");
	m["John"] += string("Stats");
	cout << m["John"] << endl;
	cout << "================================END==========================\n";
	return 0;
}