/* Author: Jonathan Dang
*  Project: Table
*  Purpose: Final Data structure
*/
#include <iostream>
#include "SQL.h"
#include "Table.h"
#include "Parcer.h"
using namespace std;

int main()
{
	/*cout << "=============================================================\n";
    vector<string> f = { "First_Name", "Last_Name", "Age", "Major" };
    Table t("People.txt", f);
    vector<string> p1 = { "Jonathan","Dang", "19", "CS" };
    vector<string> p2 = { "Sean","Leung", "22", "CS" };
    vector<string> p3 = { "Tony","Lam", "19", "Business" };
    t.insert_into(p1);
    t.insert_into(p2);
    t.insert_into(p3);
    cout << t.select_all();
    cout << "=============================================================\n";

    cout << "SQL Command: Create table NewTest.txt fields First, Last, Major, Age" << endl;
    string command_string = "Create Table NewTest.txt Fields First, Last, Major, Age";
    Parcer p(command_string);
    MMap<string, string> map;
    if (p.ptree(map))
    {
        cout << map << endl;
    }
    else
    {
        cout << "Test Failed!\n";
    }

    if (map["command"].front() == "CREATE")
    {
        Table newT(map["table"].front(), map["fields"]);
    }
    else
    {
        cout << "TEST FAILED!\n";
        exit(1);
    }
    cout << "=============================================================\n";

    cout << "SQL Command: Insert into NewTest.txt fields \"Joe John\", Smith, CS, 20" << endl;
    p.set_command("Insert into NewTest.txt fields \"Joe John\", Smith, CS, 20");
    map.clear();
    if (p.ptree(map))
    {
        cout << map << endl;
    }
    else
    {
        cout << "Test Failed!\n";
        exit(1);
    }

    if (map["command"].front() == "INSERT")
    {
        Table table(map["table"].front());
        table.insert_into(map["fields"]);
        cout << table << endl;
    }
    else
    {
        cout << "TEST FAILED!\n";
        exit(1);
    }

    cout << "=============================================================\n";
    cout << "SQL Command: Select First from NewTest.txt" << endl;
    p.set_command("Select First from NewTest.txt");
    if (p.ptree(map))
    {
        cout << map << endl;
    }
    else
    {
        cout << "Test Failed!\n";
        exit(1);
    }

    if (map["command"][0] == "SELECT")
    {
        Table table(map["table"].front());
        cout << table.select(map["fields"]);
    }
    else
    {
        cout << "Test Failed!\n";
        exit(1);
    }

    cout << "=============================================================\n";
    cout << "SQL Command: Select First_Name from People.txt where Major = CS" << endl;
    p.set_command("Select First_Name from People.txt where Major = CS and Age = 19");
    if (p.ptree(map))
    {
        cout << map << endl;
    }
    else
    {
        cout << "Test Failed!\n";
        exit(1);
    }
    Table table(map["table"][0]);
    cout << table.select(map["fields"], map["condition"]) << endl;


    cout << "=============================================================\n";
    cout << "SQL Command: Select First_Name, Last_Name from People.txt where Age < 20\n";
    p.set_command("Select First_Name, Last_Name from People.txt where Age < 20");
    if (p.ptree(map))
    {
        cout << map << endl;
    }
    else
    {
        cout << "Test Failed!\n";
        exit(1);
    }
    Table table2(map["table"][0]);
    cout << table.select(map["fields"], map["condition"]) << endl;


    cout << "=============================================================\n";
    cout << "SQL Command: Select * from People.txt\n";
    p.set_command("Select * from People.txt");
    if (p.ptree(map))
    {
        cout << map << endl;
    }
    else
    {
        cout << "Test Failed!\n";
        exit(1);
    }
    Table tlast(map["table"][0]);
    cout << tlast.select(map["fields"]) << endl;*/
    SQL sql;
    sql.run();
	cout << "================================END==========================\n";
	return 0;
}