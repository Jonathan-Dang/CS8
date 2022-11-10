#include "Parcer.h"

int Parcer::_states[MAXROW][MAXCOL];

Parcer::Parcer() : _command(""),_tokenizer()
{
	_initialize_machine(_states);
	_fill_keyword_table();
}

Parcer::Parcer(const string& command) : _command(command)
{
	_initialize_machine(_states);
	_fill_keyword_table();
	_tokenizer.set_string(command.c_str());
}

void Parcer::set_command(const string& command)
{
	_command = command;
	_tokenizer.set_string(_command.c_str());
}

bool Parcer::ptree(MMap<string, string>& map)
{
	map.clear();
	vector<string> v_q;
	Token t;
	string hold, buffer = "";
	bool quot = false;
	while (!_tokenizer.done())
	{
		_tokenizer >> t;
		if (t.token_str() == "\"")
		{
			quot = !quot;
			if (hold != "")
			{
				v_q.push_back(hold);
				hold = "";
			}
		}
		else if (t.token_str() == ".")
			buffer += t.token_str();
		else if (t.token_str() == ",")
		{
			if (!buffer.empty())
			{
				v_q.push_back(buffer);
				buffer.clear();
			}
			v_q.push_back(t.token_str());
		}
		else if (t.token_str() != " " && t.token_str() != "\t")
		{
			if (quot)
			{
				hold += t.token_str();
			}
			else
				buffer += t.token_str();
		}
		else if (t.token_str() == " " && !quot)
		{
			if (!buffer.empty())
				v_q.push_back(buffer);
			buffer.clear();
		}
		else
		{
			if (quot)
			{
				hold += t.token_str();
			}
		}
	}
	v_q.push_back(buffer);
	
	bool conditional = false; // true when applied keyword WHEN is activated
	bool name = false; //true when into or from is activated to write into name
	int row = 0;
	for (int i = 0; i < v_q.size(); i++)
	{
		int col = 0;
		string toUpper = v_q[i];
		Uppercased(toUpper);
		if (_keyword_table.contains(toUpper))
		{
			col = _keyword_table[toUpper];
		}
		else
		{
			col = SYMBOL;
		}

		int succ = _states[row][col];

		if (succ == -1)
		{
			if (!is_success(_states, row))
			{
				cout << "INVALID SQL STATEMENT\n";
				map.clear();
				return false;
			}
		}

		switch (col)
		{
		case(SYMBOL):
		{
			if (!conditional) // Meaning this is the command stage
			{
				if (name)
				{
					map["table"] += v_q[i];
				}
				else
				{
					map["fields"] += v_q[i];
				}
			}
			else //This is the conditional stage
			{
				map["condition"] += v_q[i];
			}
			break;
		}
		case(OR):
		case(AND):
		{
			map["condition"] += v_q[i];
			break;
		}
		case(INSERT):
		case(DELETE):
		case(CREATE):
		case(SELECT):
		case(DROP):
		case(SEARCH):
		{
			map["command"] += toUpper;
			break;
		}
		case(STAR):
		{
			map["fields"] += v_q[i]; 
			break;
		}
		case(FROM):
		{
			name = true;
			break;
		}
		case(INTO):
		{
			name = true;
			break;
		}
		case(WHERE):
		{
			conditional = true;
			break;
		}
		case(TABLE):
		{
			name = true;
			break;
		}
		case(FIELDS):
		{
			name = false;
			break;
		}
		case(BATCH):
		{
			map["command"] += toUpper;
			name = true;
			break;
		}
		default: //This means AND and COMMA are disregared
			break;
		}
		row = succ;
	}
	return true;
}

void Parcer::_initialize_machine(int _state[][MAXCOL])
{
	//ENUM LISTED:
	//SYMBOL = 1, SEARCH = 2, STAR = 3, FROM = 4, COMMA = 5, SELECT = 11
	//WHERE = 6, INSERT = 7, INTO = 8, DELETE = 9, CREATE = 10, MAKE = 10

	//Everything is now -1
	init_table(_states);

	//Marking Success/Fail States
	mark_fail(_states, 0);
	mark_fail(_states, 1);
	mark_fail(_states, 2);
	mark_fail(_states, 3);
	mark_fail(_states, 4);
	mark_success(_states, 5);
	mark_fail(_states, 6);
	mark_success(_states, 7);
	mark_fail(_states, 8);
	mark_fail(_states, 9);
	mark_fail(_states, 10);
	mark_success(_states, 11);
	mark_fail(_states, 12);

	//KEY WORDS ARE:
	//		SEARCH, STAR, FROM, COMMA, WHERE, INSERT, INTO, DELETE, CREATE, MAKE SYMBOL
	//COMMAND KEY WORDS ARE:
	//		SEARCH, WHERE, INSERT, DELETE, CREATE, MAKE, SELECT
	//HELPER KEYWORDS ARE:
	//		STAR, FROM, COMMA, INTO
	//SPECIAL KEY WORD FOR CONDITIONALS:
	//		WHERE
	//ANY OTHER NAMES/CONDITIONALS:
	//		SYMBOL

	//Command comes first
	mark_cell(0, _states, SEARCH, 1);
	mark_cell(0, _states, INSERT, 1);
	mark_cell(0, _states, DELETE, 1);
	mark_cell(0, _states, CREATE, 1);
	mark_cell(0, _states, MAKE, 1);
	mark_cell(0, _states, SELECT, 1);

	//Then a symbol or a star, Not sure what the star does
	mark_cell(1, _states, STAR, 2);
	mark_cell(1, _states, SYMBOL, 2);
	//Include a comma in stage 2, Using stage 3 as a Booster stage
	mark_cell(2, _states, COMMA, 3);
	mark_cell(3, _states, SYMBOL, 2);

	//Into the helper commands
	mark_cell(2, _states, FROM, 4);
	mark_cell(2, _states, INTO, 4);

	//Name of the table, also a success state
	mark_cell(4, _states, SYMBOL, 5);

	//But if there is a where!
	mark_cell(5, _states, WHERE, 6);

	//Follow where with only symbols
	mark_cell(6, _states, SYMBOL, 7);
	mark_cell(7, _states, SYMBOL, 7);
	mark_cell(7, _states, AND, 8);
	mark_cell(7, _states, OR, 8);
	mark_cell(8, _states, SYMBOL, 7);

	//Special Case for Create
	mark_cell(1, _states, TABLE, 9);
	mark_cell(9, _states, SYMBOL, 10);
	mark_cell(10, _states, FIELDS, 11);
	mark_cell(11, _states, SYMBOL, 11);
	mark_cell(11, _states, COMMA, 12);
	mark_cell(12, _states, SYMBOL, 11);

	//Insert Into <Table name> fields <Fields>
	mark_cell(1, _states, INTO, 20);
	mark_cell(20, _states, SYMBOL, 21);
	mark_cell(21, _states, COMMA, 20);
	mark_cell(21, _states, FIELDS, 22);
	mark_cell(22, _states, SYMBOL, 23);
	mark_cell(23, _states, COMMA, 22);

	mark_fail(_states, 20);
	mark_fail(_states, 21);
	mark_fail(_states, 22);
	mark_success(_states, 23);

	//Batch <filename>
	mark_fail(_states, 25);
	mark_success(_states, 26);
	mark_cell(0, _states, BATCH, 25);
	mark_cell(25, _states, SYMBOL, 26);

	//Drop Table <filename>
	mark_cell(0, _states, DROP, 27);
	mark_cell(27, _states, TABLE, 28);
	mark_cell(28, _states, SYMBOL, 29);
	mark_fail(_states, 27);
	mark_fail(_states, 28);
	mark_success(_states, 29);
}

void Parcer::_fill_keyword_table()
{
	//ENUM LISTED:
	//SYMBOL = 1, SEARCH = 2, STAR = 3, FROM = 4, COMMA = 5, SELECT = 11
	//WHERE = 6, INSERT = 7, INTO = 8, DELETE = 9, CREATE = 10, MAKE = 10, TABLE = 20, FIELDS = 21
	_keyword_table["SEARCH"] = SEARCH;
	_keyword_table["*"] = STAR;
	_keyword_table["FROM"] = FROM;
	_keyword_table["WHERE"] = WHERE;
	_keyword_table["INSERT"] = INSERT;
	_keyword_table["INTO"] = INTO;
	_keyword_table[","] = COMMA;
	_keyword_table["AND"] = AND;
	_keyword_table["OR"] = OR;
	_keyword_table["SELECT"] = SELECT;
	_keyword_table["DELETE"] = DELETE;
	_keyword_table["DROP"] = DROP;
	_keyword_table["CREATE"] = CREATE;
	_keyword_table["TABLE"] = TABLE;
	_keyword_table["MAKE"] = MAKE;
	_keyword_table["FIELDS"] = FIELDS;
	_keyword_table["VALUES"] = VALUES;
	_keyword_table["BATCH"] = BATCH;

	/*cout << "DEBUG: _keyword_table:\n";
	cout << _keyword_table << endl;*/
}

void Parcer::Uppercased(string& str)
{
	transform(str.begin(), str.end(), str.begin(), ::toupper);
}
