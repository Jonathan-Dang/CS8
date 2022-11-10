#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

bool file_exists(const char filename[]);

void open_fileRW(fstream& f, const char filename[]) throw(char*);

void open_fileW(fstream& f, const char filename[]);

void write_info(fstream& f, const char filename[], const vector<string>& v);

void read_info(fstream& f, const char filename[], vector<string>& v);

inline bool file_exists(const char filename[])
{
    const bool debug = false;
    fstream ff;
    ff.open(filename,
        std::fstream::in | std::fstream::binary);
    if (ff.fail()) {
        if (debug) cout << "file_exists(): File does NOT exist: " << filename << endl;
        return false;
    }
    if (debug) cout << "file_exists(): File DOES exist: " << filename << endl;
    ff.close();
    return true;
}

inline void open_fileRW(fstream& f, const char filename[]) throw(char*)
{
    const bool debug = false;
    //openning a nonexistent file for in|out|app causes a fail()
    //  so, if the file does not exist, create it by openning it for
    //  output:
    if (!file_exists(filename)) {
        //create the file
        f.open(filename, std::fstream::out | std::fstream::binary);
        if (f.fail()) {
            cout << "file open (RW) failed: with out|" << filename << "]" << endl;
            throw("file RW failed  ");
        }
        else {
            if (debug) cout << "open_fileRW: file created successfully: " << filename << endl;
        }
    }
    else {
        f.open(filename,
            std::fstream::in | std::fstream::out | std::fstream::binary);
        if (f.fail()) {
            cout << "file open (RW) failed. [" << filename << "]" << endl;
            throw("file failed to open.");
        }
    }

}
inline void open_fileW(fstream& f, const char filename[]) {
    f.open(filename,
        std::fstream::out | std::fstream::binary);
    if (f.fail()) {
        cout << "file open failed: " << filename << endl;
        throw("file failed to open.");
    }

}

inline void write_info(fstream& f, const char filename[], const vector<string>& v) //Ignore for now
{
    open_fileRW(f, filename);
    for (int i = 0; i < v.size(); i++)
    {
        f.write(v[i].c_str(), sizeof(v[i]));
    }
}
inline void read_info(fstream& f, const char filename[], vector<string>& v) //Ignore for now
{
    //
}

