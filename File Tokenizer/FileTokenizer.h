#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include "../STokenizer-StateMachine/STokenizer.h"
using namespace std;

class FTokenizer
{
public:
    FTokenizer(const char* fname);

    Token next_token();

    bool more();            //returns the current value of _more

    friend FTokenizer& operator >> (FTokenizer& f, Token& t)
	{
		t = f.next_token();

		if (t.token_str().empty())
			if (f.get_new_block())
				t = f.next_token();

		return f;
	}

private:
    bool get_new_block();   //Gets the new block from the file, Returns Success State
    std::ifstream instream; //File being Tokenized
    STokenizer _stk;        //The STokenizer object to tokenize current block
};


FTokenizer::FTokenizer(const char* fname)
{
	instream.open(fname);
	get_new_block();
}

Token FTokenizer::next_token()
{
	Token t;
	_stk >> t;

	return t;
}

bool FTokenizer::more()
{
	return !(instream.eof() && _stk.done());
}

bool FTokenizer::get_new_block()
{
	if (!more())
		return false;

	char s[MAX_BUFFER];
	instream.read(s, MAX_BUFFER - 1);
	s[instream.gcount()] = char(NULL);
	_stk.set_string(s);

	return true;
}
