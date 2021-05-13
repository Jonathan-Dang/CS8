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
    friend STokenizer& operator >> (STokenizer& s, Token& t)
	{
		string str;

		s.get_token(0, str);

		t = Token(str, get_type(str, s._table));
		return s;
	}

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

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer() : _pos(0)
{
	for (int i = 0; i < MAX_BUFFER; i++)
	{
		_buffer[i] = NULL;
	}
	make_table(_table);
}

STokenizer::STokenizer(const char str[]) : _pos(0)
{
	strcpy_s(_buffer, MAX_BUFFER - 1, str);
	make_table(_table);
}

bool STokenizer::done()
{
	return !more();
}

bool STokenizer::more()
{
	return _buffer[_pos] != NULL;
}

void STokenizer::set_string(const char str[])
{
	strcpy_s(_buffer, MAX_BUFFER, str);
	_pos = 0;
}

void STokenizer::make_table(int _table[][MAX_COLUMNS])
{
	init_table(_table);

	// DIGIT SECTION
	mark_fail(_table, 0);
	mark_success(_table, 1);
	mark_fail(_table, 2);
	mark_success(_table, 3);

	mark_cells(0, _table, 48, 58, 1);
	mark_cells(1, _table, 48, 58, 1);
	mark_cell(0, _table, '.', 1);
	mark_cell(1, _table, '.', 2);
	mark_cells(2, _table, 48, 58, 3);
	mark_cells(3, _table, 48, 58, 3);

	// ALPHA SECTION
	mark_success(_table, 4);
	mark_cells(0, _table, "ALPHA", 4);
	mark_cells(4, _table, "ALPHA", 4);

	// PUNC SECTION
	mark_success(_table, 5);
	mark_success(_table, 10);
	mark_cells(0, _table, "PUNC", 5);
	mark_cells(0, _table, '.', '.', 5);
	mark_cell(0, _table, ' ', 10);
	mark_cell(0, _table, '\t', 10);
	mark_cell(0, _table, '*', 5);
	mark_cell(0, _table, '=', 5);
	mark_cell(0, _table, '+', 5);
	mark_cell(0, _table, '>', 5);
	mark_cell(0, _table, '<', 5);
	// MATH SECTION
	mark_cell(5, _table, '=', 5);
	mark_cell(5, _table, '+', 5);
	mark_cell(5, _table, '>', 5);
	mark_cell(5, _table, '<', 5);
	mark_cell(5, _table, '!', 5);

}

bool STokenizer::get_token(int start_state, string& token)
{
	if (done())
		return true;

	string Tbuffer;
	int TBpos = _pos;
	int state = start_state;
	char c = _buffer[_pos];

	if (c < 32 || 127 < c)
	{
		++_pos;
		token += c;

		return true;
	}

	int new_state = _table[state][c];

	while (_buffer[TBpos] != NULL && new_state != -1)
	{
		if (!is_success(_table, new_state))
		{
			Tbuffer += c;
			state = new_state;
			c = _buffer[TBpos++];
			new_state = _table[start_state][c];

			if (!(c != NULL && new_state != -1
				&& is_success(_table, new_state)))
				return true;

			while (c != NULL && new_state != -1
				&& is_success(_table, new_state))
			{
				state = new_state;
				c = _buffer[TBpos++];
				new_state = _table[start_state][c];
				Tbuffer += c;
			}

			if (new_state == -1 || c == NULL)
			{
				token += Tbuffer;
				_pos = TBpos++;
				return true;
			}
		}
		else
		{
			token += c;
			_pos++;
			state = new_state;
		}

		c = _buffer[_pos];
		new_state = _table[state][c];
		TBpos = _pos;
	}
	return true;
}