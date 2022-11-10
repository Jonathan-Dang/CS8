#include "SQL.h"

void SQL::run_batch(const string& filename)
{
	cout << "=============================================================\n";
	cout << "              BEGINNING SQL BATCH RUN : " << filename << endl;
	cout << "=============================================================\n";

	ifstream f;
	if (!file_exists(filename.c_str()))
	{
		cout << "ERROR: File not found!\n";
		return;
	}
	f.open(filename.c_str());
	int command_num = 0;
	while (!f.eof())
	{
		string com;
		getline(f, com);
		if (com != "")
		{
			if (com[0] != '/')
			{
				cout << "[" << command_num << "] " << com << endl;
				command_num++;
			}
			run_command(com);
			if(com[0] != '/')
				cout << endl << endl;
		}
	}
	cout << endl << endl;
	cout << "=============================================================\n";
	cout << "                   FINISHED SQL BATCH RUN" << endl;
	cout << "=============================================================\n";
}

SQL::SQL()
{
	//We need to grab the filenames saved on disk, then input it into the map
	const string _LOG = "LOG.txt"; // This is the file name where we will be grabing from
	ifstream ins;
	if (!file_exists(_LOG.c_str())) //if it doesn't exist, then there were no tables, Nothing to do here
	{
		return;
	}

	ins.open(_LOG);
	while (!ins.eof())
	{
		string tablename;
		ins >> tablename;
		if(tablename != "")
			_management[tablename] = Table(tablename);
	}
}

SQL::~SQL()
{
	//We need to save the specific table names to be reopened later
	const string _LOG = "LOG.txt"; // This is the file name where we will be storing tables from
	ofstream outs;
	outs.open(_LOG.c_str());
	if (!_management.empty())
	{
		for (auto it : _management)
		{
			outs << it.key << endl;
		}
	}
}

void SQL::run()
{
	cout << "SQL START!\n";
	cout << endl << endl << endl;

	cout << "----------SQL MANAGEMENT----------\n";
	if (file_exists("LOG.txt") && !_management.empty())
	{
		for (auto it : _management)
		{
			cout << it.key << endl;
		}
	}
	else
		cout << "EMPTY!\n";
	cout << "----------------------------------\n";

	cout << endl << endl;
	while (true)
	{
		string input;
		cout << endl;
		cout << "> ";
		getline(cin, input);
		string exit_portion = input;
		transform(exit_portion.begin(), exit_portion.end()
			, exit_portion.begin(), ::toupper);
		if (exit_portion == "EXIT")
			break;
		else if (input == "");
		else
			run_command(input);
	}
}

void SQL::run_command(const string& command)
{
	_parcer.set_command(command);
	if (command[0] == '/' && command[1] == '/')
	{
		cout << command << endl;
		return;
	}
	if (!_parcer.ptree(_map))
	{
		return;
	}

	if (_map["command"][0] == "CREATE" || _map["command"][0] == "MAKE")
	{
		if (_management.contains(_map["table"][0]))
		{
			cout << "ERROR: Table with the same name already exists!\n";
			return;
		}
		Table table(_map["table"][0], _map["fields"]);
		_management[_map["table"][0]] = table;
	}
	else if (_map["command"][0] == "INSERT")
	{
		if (!_management.contains(_map["table"][0]))
		{
			cout << "ERROR: Table does not exist!\n";
			return;
		}
		_management[_map["table"][0]].insert_into(_map["fields"]);
	}
	else if (_map["command"][0] == "SELECT")
	{
		if (!_management.contains(_map["table"][0]))
		{
			cout << "ERROR: Table does not exist!\n";
			return;
		}

		if (!_map["condition"].empty())
		{
			cout << _management[_map["table"][0]].select(_map["fields"], _map["condition"]);
		}
		else
			cout << _management[_map["table"][0]].select(_map["fields"]);
	}
	else if (_map["command"][0] == "DELETE")
	{
		if (!_management.contains(_map["table"][0]))
		{
			cout << "ERROR: Table does not exist!\n";
			return;
		}

		//Not Done
	}
	else if (_map["command"][0] == "DROP")
	{
		if (!_management.contains(_map["table"][0]))
		{
			cout << "ERROR: Table does not exist!\n";
			return;
		}

		_management[_map["table"][0]].drop_table();
		_management.erase(_map["table"][0]);
	}
	else if (_map["command"][0] == "BATCH")
	{
		run_batch(_map["table"][0]);
	}

	cout << "SQL: DONE\n";
}
