#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <string>
#include <cstring>
#include "Record.h"
#include <iomanip>
#include <algorithm>
#include <stack>
#include "../BPlus Tree Based Maps/MMap.h"
#include "../BPlus Tree Based Maps/Map.h"
using namespace std;

class Table
{
public:
	//Constructor
	Table();
	Table(const string& filename);
	Table(const string& filename, const vector<string>& fields);
	
	//Field Manipulation
	void set_fields(const vector<string>& fields);
	vector<string>& get_fields();

	//Insert into record
	void insert_into(const vector<string>& fields);
	void insert_into(Record& r);

	//Selecting Within Table
	Table select_all();
	Table select(const vector<string>& fields);
	Table select(const vector<string>& fields, const vector<string>& conditional);

	//Delete a row from the table
	void drop_table();
	void delete_selected(const vector <string>& fields);
	void delete_selected(const vector<string>& fields, const vector<string>& conditional);

	//Functionality
	bool empty() { return _last_record == 0; }
	friend ostream& operator <<(ostream& outs, const Table& t);
private:
	int _serial;
	long _last_record;
	string _filename;
	vector<string> _fields;
	vector<MMap<string, long>> _index; // Key: Value from the Record | Value: Record Number
	Map<string, int> _index_directory; //Mapping to each Field and respective Multimap

	void reindex();
	vector<string> postfix(vector<string> conditional);
	vector<long> RPN(vector<string> post);
	static Map<string, int> _operators;
};

enum OPERATORS : int
{
	EQUAL = 1,
	NOT_EQUAL = 2,
	GREATER = 3,
	GREATER_EQUAL = 4,
	LESSER = 5,
	LESSER_EQUAL = 6,
	SYMBOL_ = 8,
	AND_ = 10,
	OR_ = 9,
	LPAR = 15,
	RPAR = 12
};