#include "Table.h"

Map<string, int> Table::_operators;

Table::Table() : _filename("UNKNOWN"),_serial(0),_last_record(0)
{
}

Table::Table(const string& filename) :_filename(filename), _serial(0)
{
	//open File 

	if (filename.substr(filename.size() - 4) != ".txt")
		_filename += ".txt";

	fstream f;
	open_fileRW(f, (filename).c_str());

	//Read first record to obtain fields
	Record r;
	long record_num = 0;

	//Set Fields
	r.read(f, record_num);
	record_num++;
	set_fields(r.get_record());
	r = Record(_fields.size());
	//Set up Index Matrix
	for (int i = 0; i < _fields.size(); i++)
	{
		_index_directory[_fields[i]] = i;
		_index.push_back(MMap<string, long>());
	}

	//Continue until all records obtained
	while (r.read(f, record_num) != 0)
	{
		vector<string> entry = r.get_record();
		for (int i = 0; i < _fields.size(); i++)
		{
			int pos = _index_directory[_fields[i]];
			_index[pos][entry[i]] += record_num;
		}
		record_num++;
	}
	_last_record = record_num;
	f.close();

	//Set up Operator Map
	_operators["="] = EQUAL;
	_operators["!="] = NOT_EQUAL;
	_operators[">"] = GREATER;
	_operators[">="] = GREATER_EQUAL;
	_operators["<"] = LESSER;
	_operators["<="] = LESSER_EQUAL;
	_operators["and"] = AND_;
	_operators["or"] = OR_;
	_operators["("] = LPAR;
	_operators[")"] = RPAR;
}

Table::Table(const string& filename, const vector<string>& fields) : _filename(filename), _serial(0)
{
	//Set Fields
	set_fields(fields);
	
	//Set Up Index Matrix
	for (int i = 0; i < fields.size(); i++)
	{
		_index_directory[fields[i]] = i;
	}

	//Writing first record as the fields given
	fstream f;
	open_fileW(f, (filename).c_str());
	Record recor(fields);
	recor.write(f);
	f.close();

	//Set up Operator Map
	_operators["="] = EQUAL;
	_operators["!="] = NOT_EQUAL;
	_operators[">"] = GREATER;
	_operators[">="] = GREATER_EQUAL;
	_operators["<"] = LESSER;
	_operators["<="] = LESSER_EQUAL;
	_operators["and"] = AND_;
	_operators["or"] = OR_;
	_operators["("] = LPAR;
	_operators[")"] = RPAR;
}

void Table::set_fields(const vector<string>& fields)
{
	for (int i = 0; i < fields.size(); i++)
	{
		_fields.push_back(fields[i]);
	}
}

vector<string>& Table::get_fields()
{
	return _fields;
}

void Table::insert_into(const vector<string>& fields)
{
	//Prepare to Write
	fstream outs;
	open_fileRW(outs, (_filename).c_str());

	//Write into the Table Using Record
	Record r(fields);
	r.write(outs);

	//reindex();
	//Close the File
	outs.close();
}

void Table::insert_into(Record& r)
{
	//Prepare to Write
	fstream outs;
	open_fileRW(outs, (_filename).c_str());
	//Write into the table
	r.write(outs);

	//reindex();
	//Close the file
	outs.close();
}

Table Table::select_all()
{
	//Preparing to Read
	fstream f;
	open_fileRW(f, (_filename).c_str());

	//Create Temp Parameters
	string temp_name = _filename;
	temp_name += "00";
	_serial++;
	temp_name += to_string(_serial);

	//Create a table
	Table table("Filtered Tables/" + temp_name,_fields);

	Record r(_fields.size());
	int record_num = 1;

	//Read from this table to the other table
	while(r.read(f, record_num) != 0)
	{
		Record temp = r;
		table.insert_into(temp);
		record_num++;
	}
	f.close();
	return table;
}

Table Table::select(const vector<string>& fields)
{
	if (fields[0] == "*")
		return select_all();

	//Obtain Position/Index of the selected Fields for all peoples
	vector<int> order;
	for (int i = 0; i < fields.size(); i++)
	{
		order.push_back(_index_directory[fields[i]]);
	}

	//Make a new Table to hold these selected values
	string temp_name = _filename;
	temp_name += "00";
	_serial++;
	temp_name += to_string(_serial);
	//This constructor creates a file!
	Table table(("Filtered Tables/" + temp_name), fields);

	//Prepare for Reading!
	fstream f;
	open_fileRW(f, ("Filtered Tables/" + _filename).c_str());

	Record r(order.size());
	long record_num = 1;
	//Inserting into new table
	while (r.read(f, record_num))
	{
		vector<string> filter;
		vector<string> data = r.get_record();
		for (int i = 0; i < order.size(); i++)
		{
			filter.push_back(data[order[i]]);
		}
		Record temp(filter);
		table.insert_into(temp);
		record_num++;
	}
	return table;
}

Table Table::select(const vector<string>& fields, const vector<string>& conditional)
{
	//Obtain Position/Index of the selected Fields for all peoples
	vector<int> order;
	vector<string> selected_fields;
	if (fields[0] == "*")
	{
		for (int i = 0; i < _fields.size(); i++)
		{
			order.push_back(_index_directory[_fields[i]]);
			selected_fields.push_back(_fields[i]);
		}
	}
	else
	{
		for (int i = 0; i < fields.size(); i++)
		{
			order.push_back(_index_directory[fields[i]]);
			selected_fields.push_back(fields[i]);
		}
	}
	//Post Fix Obtainable
	vector<string> post = postfix(conditional);

	//Make a new Table to hold these selected values
	string temp_name = _filename;
	temp_name += "00";
	_serial++;
	temp_name += to_string(_serial);
	//This constructor creates a file!
	Table table(("Filtered Tables/" + temp_name).c_str(), selected_fields);

	vector<long> records = RPN(post);

	//Now Read the records specified and insert it into the new table!
	fstream f;
	open_fileRW(f, ((_filename).c_str()));
	Record r(selected_fields.size());
	for (int i = 0; i < records.size(); i++)
	{
		r.read(f, records[i]);
		vector<string> filter;
		vector<string> data = r.get_record();
		for (int i = 0; i < order.size(); i++)
		{
			filter.push_back(data[order[i]]);
		}
		Record temp(filter);
		table.insert_into(temp);
	}

	return table;
}

void Table::drop_table()
{
	_index.~vector();
	_index_directory.clear();
	_serial = 0;
	_last_record = 0;
	_fields.clear();
	std::remove((_filename).c_str());
	_filename = "UNKNOWN";
}

void Table::reindex()
{
	_index.~vector();
	_index_directory.clear();
	//Set up Index Matrix
	for (int i = 0; i < _fields.size(); i++)
	{
		_index_directory[_fields[i]] = i;
		_index.push_back(MMap<string, long>());
	}

	Record r(_fields.size());
	long record_num = 1;
	fstream f;
	open_fileRW(f, (_filename).c_str());

	//Continue until all records obtained
	while (r.read(f, record_num) != 0)
	{
		vector<string> entry = r.get_record();
		for (int i = 0; i < _fields.size(); i++)
		{
			int pos = _index_directory[_fields[i]];
			_index[pos][entry[i]] += record_num;
		}
		record_num++;
	}
	_last_record = record_num;
	f.close();
}

vector<string> Table::postfix(vector<string> conditional)
{
	vector<string> post, Operators;
	for (int i = 0; i < conditional.size(); i++)
	{
		int ID = 0;
		if (_operators.contains(conditional[i]))
			ID = _operators[conditional[i]];
		else
			ID = SYMBOL_;

		int temp = 0;

		switch (ID)
		{
		case(SYMBOL_):
		{
			post.push_back(conditional[i]);
			break;
		}
		case(EQUAL):
		case(NOT_EQUAL):
		case(GREATER):
		case(GREATER_EQUAL):
		case(LESSER):
		case(LESSER_EQUAL):
		{
			if (Operators.empty())
				Operators.push_back(conditional[i]);
			else if (_operators[Operators.back()] >= ID
				&& Operators.back() != "(" && Operators.back() != "or" 
				&& Operators.back() != "and")
			{
				string hold = Operators.back();
				Operators.pop_back();
				Operators.push_back(conditional[i]);
				post.push_back(hold);
			}
			else
				Operators.push_back(conditional[i]);
			break;
		}
		case(OR_):
		case(AND_):
		{
			string hold = Operators.back();
			Operators.pop_back();
			post.push_back(hold);
			Operators.push_back(conditional[i]);
			break;
		}
		case(LPAR):
		{
			Operators.push_back(conditional[i]);
			break;
		}
		case(RPAR):
		{
			while(!Operators.empty() && Operators.back() != "(")
			{
				string hold = Operators.back();
				Operators.pop_back();
				post.push_back(hold);
			}
			Operators.pop_back();
			break;
		}
		default:
			break;
		}
	}
	while (!Operators.empty())
	{
		string hold = Operators.back();
		Operators.pop_back();
		post.push_back(hold);
	}

	return post;
}

vector<long> Table::RPN(vector<string> post)
{
	reindex();
	//Proceed to obtain record numbers from the specified filters

	stack<vector<long>> data, filters;

	long index = -1;
	long oper = 0;
	for (int i = 0; i < post.size(); i++)
	{
		if (_index_directory.contains(post[i]))
			index = _index_directory[post[i]];
		else if (index >= 0) //At this point, post[i - 1] will be a symbol, aka a target for filtering
						   //post[i] is the operator!
		{
			if (_operators.contains(post[i]))
				oper = _operators[post[i]];
			switch (oper)
			{
			case(EQUAL):
			{
				data.push(_index[index][post[i - 1]]);

				break;
			}//EQUAL
			case(GREATER):
			{
				MMap<string, long> target_mmap = _index[index];
				//Check if there is a lower bound
				if (target_mmap.lower_bound(post[i - 1]) == target_mmap.end())
					break;

				//Calculate the pos
				vector<long> tempStorage;
				for (MMap<string, long>::Iterator it = target_mmap.lower_bound(post[i - 1])
					; it != target_mmap.end(); it++)
				{
					if (it != target_mmap.lower_bound(post[i - 1]))
					{
						tempStorage = Union((*it).value_list, tempStorage);
					}
				}
				data.push(tempStorage);
				break;
			}//GREATER | lower_bound | not including, but starting
			case(GREATER_EQUAL):
			{
				MMap<string, long> target_mmap = _index[index];
				//Check if there is a lower bound
				if (target_mmap.lower_bound(post[i - 1]) == target_mmap.end())
					break;

				vector<long> tempStorage;
				//Calculate the pos
				for (MMap<string, long>::Iterator it = target_mmap.lower_bound(post[i - 1])
					; it != target_mmap.end(); it++)
				{
					tempStorage = Union((*it).value_list, tempStorage);
				}

				if (target_mmap.lower_bound(post[i - 1]) != target_mmap.end())
				{
					tempStorage = Union((*target_mmap.lower_bound(post[i - 1])).value_list, tempStorage);
				}

				data.push(tempStorage);
				break;
			}//GREATER_EQUAL | lower_bound | including and starting
			case(LESSER):
			{
				MMap<string, long> target_mmap = _index[index];
				//Check if there is a lower bound
				if (target_mmap.upper_bound(post[i - 1]) == target_mmap.end())
					break;

				vector<long> tempStorage;
				//Calculate the pos
				for (MMap<string, long>::Iterator it = target_mmap.begin()
					; it != target_mmap.upper_bound(post[i - 1]); it++)
				{
					tempStorage = Union((*it).value_list, tempStorage);
				}

				data.push(tempStorage);
				break;
			}//LESSER | upper_bound
			case(LESSER_EQUAL):
			{
				MMap<string, long> target_mmap = _index[index];
				//Check if there is a lower bound
				if (_index[index].lower_bound(post[i - 1]) == target_mmap.end())
					break;


				vector<long> tempStorage;
				//Calculate the pos
				for (MMap<string, long>::Iterator it = target_mmap.begin()
					; it != target_mmap.upper_bound(post[i - 1]); it++)
				{
					tempStorage = Union((*it).value_list, tempStorage);
				}

				if (target_mmap.upper_bound(post[i - 1]) != target_mmap.end())
				{
					tempStorage = Union((*target_mmap.upper_bound(post[i-1])).value_list, tempStorage);
				}
				data.push(tempStorage);
				break;
			}//LESSER_EQUAL | upper_bound
			case(AND_):
			{
				if (data.size() < 2)
					break;

				vector<long> a, b, AND;

				a = data.top();
				data.pop();
				b = data.top();
				data.pop();

				AND = Intersection(a, b);
				data.push(AND);
				break;
			}//AND_
			case(OR_):
			{
				if (data.size() < 2)
					break;
				vector<long> a, b, OR;

				a = data.top();
				data.pop();
				b = data.top();
				data.pop();

				OR = Union(a, b);
				data.push(OR);
				break;
			}//OR_
			default:
				break;
			}
			oper = 0;
		}
	}

	if (data.empty())
		return vector<long>();
	return data.top();
}

ostream& operator<<(ostream& outs, const Table& t)
{
	Record r;
	long record_num = 0;
	fstream f;
	open_fileRW(f, (t._filename).c_str());
	r.read(f, record_num);
	record_num++;
	outs << left << setw(20) << "Record No.";
	for (int i = 0; i < t._fields.size(); i++)
	{
		outs << left << setw(20) << t._fields[i];

	}
	outs << endl;
	for (int i = 0; i < t._fields.size(); i++)
	{
		outs << "------------------------";
	}
	outs << " " << endl;
	while (r.read(f, record_num) != 0)
	{
		outs << left << setw(20) << record_num - 1 << r << endl;
		record_num++;
	}
	return outs;
}
