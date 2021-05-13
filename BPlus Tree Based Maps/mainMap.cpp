/* Author: Jonathan Dang
*  Project: BPT based Maps
*  Purpose: DATA STRUCTURE
*/
#include <iostream>
#include <string>
#include "Map.h"
#include "MMap.h"
#include "../File Tokenizer/FileTokenizer.h"

using namespace std;

MMap<string, long> get_word_indices(const char* file_name);
void test_map_auto(int size);
void test_multimap_auto(int size);

int main()
{
	cout << "=============================================================\n";
	MMap<string, long> word_indices;
	word_indices = get_word_indices("solitude.txt");
	cout << endl << endl << endl;

	//list all nodes of the index mmap:
	for (MMap<string, long>::Iterator it = word_indices.begin();
		it != word_indices.end(); it++) {
		cout << *it << endl;
	}


	cout << endl << endl << endl;
	cout << "---------------------------------------------------" << endl;
	string this_word = "ice";
	cout << "---------------------------------------------------" << endl;
	cout << "Indices of \"" << this_word << "\"" << endl;
	//list indices of this_word:
	if (word_indices.contains(this_word)) {
		cout << this_word << ": " << word_indices[this_word] << endl;
	}
	cout << endl << endl << endl;

	cout << "---------------------------------------------------" << endl;
	string from = "ask";
	string to = "asker";
	//list from .. to:
	cout << "listing indices from \"" << from << "\" to \"" << to << "\"" << endl;
	cout << "---------------------------------------------------" << endl;
	for (MMap<string, long>::Iterator it =
		word_indices.lower_bound(from);
		it != word_indices.upper_bound(to) &&
		it != word_indices.end(); it++) {
		cout << *it << endl;
	}
	/*Map<int, int> map;
	for (int i = 0; i < 100; i++)
	{
		map[i + 1] = i + 1;
	}
	for (Map<int, int>::Iterator it = map.begin(); it != map.end(); it++)
	{
		cout << *it << endl;
	}
	cout << "=============================================================\n";
	MMap<int, int> mmap;
	for (int i = 0; i < 100; i++)
	{
		for (int t = 0; t < 5; t++)
		{
			mmap[i + 1] += t;
		}
	}
	for (MMap<int, int>::Iterator it = mmap.lower_bound(40); it != mmap.upper_bound(50); it++)
	{
		cout << *it << endl;
	}
	MMap<string, int> smap;
	smap["a"] += 1;
	smap["b"] += 2;
	smap["c"] += 3;
	for (MMap<string, int>::Iterator it = smap.begin(); it != smap.upper_bound("b"); it++)
	{
		cout << *it << endl;
	}*/
	/*cout << "MAP STRESS TEST\n";
	test_map_auto(1000);
	cout << "MULTI-MAP STRESS TEST\n";
	test_multimap_auto(1000);*/
	cout << "===============================END===========================\n";
	return 0;
}

void test_map_auto(int size)
{
	bool verified = true;
	const int MAX = 10000;
	assert(size < 10000);
	Map<double, double> m;
	int a[MAX] = {};
	int b[MAX] = {};
	for (int i = 0; i < size; i++)
	{
		a[i] = i;
		b[i] = i + 10000;
	}

	for (int i = 0; i < size; i++)
	{
		m[a[i]] = b[i];
	}

	for (int i = 0; i < size; i++)
	{
		if (m[a[i]] != b[i])
		{
			verified = false;
			break;
		}
	}

	cout << "**************************************************************************" << endl;
	cout << "**************************************************************************" << endl;
	cout << "             E N D     T E S T:  items: " << size << " ";
	cout << (verified ? "VERIFIED" : "VERIFICATION FAILED") << endl;
	cout << "**************************************************************************" << endl;
	cout << "**************************************************************************" << endl;
}

void test_multimap_auto(int size)
{
	bool verified = true;
	const int MAX = 10000;
	assert(size < 10000);
	MMap<double, double> m;
	int a[MAX] = {};
	int b[MAX] = {};
	for (int i = 0; i < size; i++)
	{
		a[i] = i;
		b[i] = i + 10000;
	}

	for (int i = 0; i < size; i++)
	{
		for (int t = 0; t < 5; t++)
		{
			m[a[i]] += b[i];
		}
	}

	for (int i = 0; i < size; i++)
	{
		vector<double> v = m[a[i]];
		for (int t = 0; t < 5; t++)
		{
			if (v[t] != b[i])
			{
				verified = false;
				break;
			}
		}
		if (!verified)
			break;
	}

	cout << "**************************************************************************" << endl;
	cout << "**************************************************************************" << endl;
	cout << "             E N D     T E S T:  items: " << size << " ";
	cout << (verified ? "VERIFIED" : "VERIFICATION FAILED") << endl;
	cout << "**************************************************************************" << endl;
	cout << "**************************************************************************" << endl;
}

MMap<string, long> get_word_indices(const char* file_name) {
	const bool debug = false;
	MMap<string, long> word_indices;
	FTokenizer ftk("solitude.txt");
	Token t;
	long count = 0;

	ftk >> t;
	while (ftk.more()) {
		//only the "words"
		if (t.type_string() == "ALPHA") {
			string s;
			s = t.token_str();
			word_indices[s] += count;
			count++;
			if (debug)
				cout << "|" << t.token_str() << "|" << endl;
		}
		ftk >> t;
	}
	return word_indices;
}