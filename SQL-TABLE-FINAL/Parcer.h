#pragma once
#include <iostream>
#include <string.h>
#include <cstring>
#include <string>
#include <algorithm>
#include "../BPlus Tree Based Maps/Map.h"
#include "../BPlus Tree Based Maps/MMap.h"
#include "STokenizer/STokenizer.h"
#include "STokenizer/StateMachine.h"
using namespace std;

enum KEYWORDS : int { SYMBOL = 1, SEARCH = 2, STAR = 3, FROM = 4, COMMA = 5, AND = 15, SELECT = 11, TABLE = 20, FIELDS = 21
						, WHERE = 6, INSERT = 7, INTO = 8, DELETE = 9, CREATE = 10, MAKE = 10, OR = 14, VALUES = 21, BATCH = 30, DROP = 19
};

class Parcer
{
public:
	Parcer();
	Parcer(const string& command);

	void set_command(const string& command);

	bool ptree(MMap<string, string>& map);

private:
	string _command;
	STokenizer _tokenizer;
	Map<string, int> _keyword_table;
	static int _states[MAXROW][MAXCOL];

	void _initialize_machine(int _state[][MAXCOL]);
	void _fill_keyword_table();
	void Uppercased(string& str);
};

