#pragma once
#include <iostream>
#include <string>
#include "StateMachine.h"
#include "Token.h"
using namespace std;

const int MAX_ROWS = 30, MAX_COLUMNS = 256, MAX_BUFFER = 500;

class STokenizer
{
public:
    STokenizer();
    STokenizer(const char str[]);
    bool done();            //true: there are no more tokens
    bool more();            //true: there are more tokens
    //

    //---------------
    //extract one token (very similar to the way cin >> works)
	friend STokenizer& operator >> (STokenizer& s, Token& t);

    //set a new string as the input string
    void set_string(const char str[]);

private:
    //create table for all the tokens we will recognize
    //                      (e.g. doubles, words, etc.)
    void make_table(int _table[][MAX_COLUMNS]);

    //extract the longest string that match
    //     one of the acceptable token types
    bool get_token(int start_state, string& token);
    //---------------------------------
    char _buffer[MAX_BUFFER + 1];   //input string
    int _pos;                       //current position in the string
    static int _table[MAX_ROWS][MAX_COLUMNS];
};
