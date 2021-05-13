/* Project: String Tokenizer
* Author: Jonathan Dang
* Purpose: To draw and seperate strings into substrings
*/
#include <iostream>
#include "STokenizer.h"
#include <iomanip>

using namespace std;

int main()
{
	cout << "=====================================\n";
	char c[500] = "Insert Into Students.txt values John, \t\t\t Johnson, \t\t\t, 20";
	STokenizer s(c);
	Token t;

	while (!s.done())
	{
		s >> t;
		cout << setw(10)<< t.type_string() << setw(10) << t << endl;
	}

	cout << "===================END===============\n";
	return 0;
}