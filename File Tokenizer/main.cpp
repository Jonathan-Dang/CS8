/* Author: Jonathan Dang
*  Project: File Tokenizer
*  Purpose: Drawing input from a file then distributing tokens.
*/
#include <iostream>
#include "FileTokenizer.h"
using namespace std;

void test_f_tokenize_simple();

int main()
{
	cout << "==================================\n";
	test_f_tokenize_simple();
	cout << "=================END===============\n";
	return 0;
}

void test_f_tokenize_simple()
{
    Token t;
    char s[20] = "solitude.txt";
    FTokenizer ftk(s);
    ftk >> t;
    int token_count = 0;
    int i = 0;
    while (ftk.more()) {
        if (t.type_string() == "ALPHA") {
            token_count++;
            cout << setw(10) << token_count
                << setw(3) << left << ":" << setw(25) << left << t.token_str()
                << t.type_string() << endl;
        }
        ftk >> t;
    }
    cout << "Tokens Found: " << token_count << endl;
    cout << "==========" << endl;

}