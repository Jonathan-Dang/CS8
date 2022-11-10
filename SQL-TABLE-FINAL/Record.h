#pragma once
#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <cstring>
#include <vector>
#include "Utility-Record.h"
#include "../Btree/Btree Functions.h"
using namespace std;

class Record 
{
public:
    Record(int num = MAX_ROWS) : _numrecord(-1), _num_fields(num)
    {
        _record[0][0] = NULL;
    }
    Record(const vector<string>& v) : _numrecord(-1), _num_fields(v.size())
    {
        //Setting the Beginning of every row to NULL
        for (int i = 0; i < MAX_ROWS; i++) 
        {
            _record[i][0] = NULL;
        }

        //Copying the vector of strings as cstrings to the 2d char array
        for(unsigned int i = 0; i < v.size(); i++) 
        {
            strcpy_s(_record[i], v[i].c_str());
        }
    }
    long write(fstream& outs);              //returns the record number
    long read(fstream& ins, long recno);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file

    vector<string> get_record();            //Returns the record as a Vector of strings
    string& operator[](int record_number);  //Returns ith row as a string

    friend ostream& operator<<(ostream& outs, const Record& r)
    {
        int i = 0;
        while (r._record[i][0] != NULL)
        {
            outs << left << setw(20) << r._record[i];
            i++;
        }
        return outs;
    }
private:
    static const int MAX_COLS = 50;
    static const int MAX_ROWS = 20;
    int _numrecord;
    int _num_fields;
    char _record[MAX_ROWS + 1][MAX_COLS + 1];
};

inline long Record::write(fstream& outs)
{
    outs.seekg(0, outs.end);
    long pos = outs.tellp();
    outs.write(&_record[0][0], sizeof(_record));
    return pos / sizeof(_record);
}

inline long Record::read(fstream& ins, long recno)
{
    long pos = recno * sizeof(_record);
    ins.seekg(pos, ios_base::beg);
    ins.read(&_record[0][0], sizeof(_record));
    return ins.gcount();
}

inline vector<string> Record::get_record()
{
    vector<string> v;
    for (int i = 0; i < _num_fields; i++)
    {
        if(_record[i][0] != NULL)
            v.push_back(string(_record[i]));
    }
    return v;
}
