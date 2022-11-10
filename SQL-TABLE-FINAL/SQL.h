#pragma once
#include "Parcer.h"
#include "Table.h"
#include <vector>

class SQL
{
public:
	SQL();
	~SQL();

	void run();
private:
	MMap<string, string> _map;
	Parcer _parcer;
	Map<string, Table> _management;
	//General Run the Command
	void run_command(const string& command);
	void run_batch(const string& filename);
};
