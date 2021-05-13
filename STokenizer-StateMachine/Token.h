#pragma once
#include <iostream>
#include <string.h>
using namespace std;

class Token
{
public:
    Token();
    Token(string str, int type);
    friend ostream& operator <<(ostream& outs, const Token& t)
	{
		outs << "|" << t._token << "|";
		return outs;
	}
    int type();
    string type_string();
    string token_str();
private:
    string _token;
    int _type;
    /*
    TYPES:
    4 | ALPHA
    1, 3 | DIGIT
    5 | PUNC
    -1 | OTHER/UNKOWN
    */
};

Token::Token()
{
	_token = string();
	_type = -1;
}

Token::Token(string str, int type) :_token(str), _type(type)
{
	//
}

int Token::type()
{
	return _type;
}

string Token::type_string() //Returns Type but in a string format ie: type: Punc
{
	if (_type == 4)
	{
		return string("ALPHA");
	}
	else if (_type == 1 || _type == 3)
	{
		return string("DIGIT");
	}
	else if (_type == 5)
	{
		return string("PUNC");
	}
	else if (_type == 10)
	{
		return string("SPACE");
	}
	else
	{
		return string("UNKOWN");
	}
}

string Token::token_str()
{
	return _token;
}