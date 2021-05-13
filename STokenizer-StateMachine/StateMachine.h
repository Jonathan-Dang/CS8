#pragma once
#include <iostream>
#include <string.h>
#include <iomanip>
#include "Token.h"
#include <string>
using namespace std;

const int MAXROW = 30, MAXCOL = 256;

//=============================================================//
//				   		FUNCTION CALLS						   //
//=============================================================//

//Fill all cells of the array with -1
inline void init_table(int _table[MAXROW][MAXCOL]);

//Mark this state (row) with a 1 (success)
inline void mark_success(int _table[][MAXCOL], int state);

//Mark this state (row) with a 0 (fail)
inline void mark_fail(int _table[][MAXCOL], int state);

//true if state is a success state
inline bool is_success(int _table[][MAXCOL], int state);

//Mark a range of cells in the array. 
inline void mark_cells(int row, int _table[][MAXCOL], int from, int to, int state);

//Mark columns represented by the string columns[] for this row
inline void mark_cells(int row, int _table[][MAXCOL], const char columns[], int state);

//Mark this row and column
inline void mark_cell(int row, int table[][MAXCOL], int column, int state);

//This can realistically be used on a small table
inline void print_table(int _table[MAXROW][MAXCOL]);

//show string s and mark this position on the string:
//hello world   pos: 7
//       ^
inline void show_string(char s[], int _pos);

//Obtains Type for token using given table
inline int get_type(string token, int table[][MAXCOL]);

//=============================================================//
//				   		FUNCTION DEFINITIONS				   //
//=============================================================//

void init_table(int _table[MAXROW][MAXCOL])
{
	for (int i = 0; i < MAXCOL; i++)
	{
		for (int t = 0; t < MAXROW; t++)
		{
			_table[t][i] = -1;
		}
	}
}

void mark_success(int _table[][MAXCOL], int state)
{
	_table[state][0] = 1;
}

void mark_fail(int _table[][MAXCOL], int state)
{
	_table[state][0] = 0;
}

bool is_success(int _table[][MAXCOL], int state)
{
	return _table[state][0] == 1;
}

void mark_cells(int row, int _table[][MAXCOL], int from, int to, int state)
{
	for (int i = from; i != to; i++)
	{
		_table[row][i] = state;
	}
}

void mark_cells(int row, int _table[][MAXCOL], const char columns[], int state)
{
	if (string("DIGIT") == columns)
	{
		mark_cells(row, _table, 48, 57, state);
	}
	else if (string("ALPHA") == columns)
	{
		for (int i = 65; i < 123; i++)
		{ //91 -> 96
			if (i > 96 || i < 91)
			{
				_table[row][i] = state;
			}
		}

		for (int i = 128; i < 169; i++)
		{
			_table[row][i] = state;
		}
	}
	else if (string("PUNC") == columns)
	{// 32-34, 38-41 44-46, 58,59,63,91,92,95,123-125
		for (int i = 32; i < 42; i++)
		{
			if (i < 35 || i > 37)
			{
				_table[row][i] = state;
			}
		}
		for (int i = 44; i < 47; i++)
		{
			_table[row][i] = state;
		}
		int temp[9] = { 58,59,63,91,92,95,123,124,125 };
		for (int i = 0; i < 9; i++)
		{
			_table[row][temp[i]] = state;
		}
	}
	else
	{
		char c = *columns;
		_table[row][c] = state;
	}
}

void mark_cell(int row, int table[][MAXCOL], int column, int state)
{
	table[row][column] = state;
}

void print_table(int _table[MAXROW][MAXCOL])
{
	for (int i = 0; i < MAXROW ; i++)
	{
		for (int t = 0; t < MAXCOL; t++)
		{
			if (t == MAXCOL-1)
			{
				cout << _table[i][t] << endl;
			}
			else
			{
				cout << _table[i][t] << " ";
			}
		}
	}
}

void show_string(char s[], int _pos)
{
	cout << s << endl;
	for (int i = 0; i < _pos; i++)	
	{
		cout << " ";
	}
	cout << "^" << endl;
}

int get_type(string token, int table[][MAXCOL])
{
	return table[0][token[0]];
}



