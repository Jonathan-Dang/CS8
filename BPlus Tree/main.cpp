/* Author: Jonathan Dang
*  Project: BPlus Tree
*  Purpose: Data Structure
*/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include "BPlus_Tree.h"
using namespace std;

void test_iterator();
void test_insert_bplustree_auto(int tree_size, int how_many);
void test_bplustree_auto(int tree_size, int how_many, bool report);
bool test_bplustree_auto(int how_many, bool report);
int Random(int lo, int hi);

int main()
{
	cout << "=============================================================\n";

    //------------------------------------------
    srand(time(0));
    //------------------------------------------
    //cout << "INSERTION STRESS TEST!\n";
    //test_insert_bplustree_auto(500, 5000);
    cout << "STRESS TEST!\n";
    test_bplustree_auto(100, 100, false);
    test_iterator();
	cout << "==============================END============================\n";
	return 0;
}

void test_iterator() {
    const bool debug = false;
    BPlusTree<int> bpt;
    for (int i = 0; i < 125; i++)
        bpt.insert(Random(0, 100));
    cout << bpt << endl;


    cout << "------------------------------------------------------------" << endl;
    for (BPlusTree<int>::Iterator it = bpt.begin();
        it != bpt.end(); ++it) {
        if (debug) it.print_Iterator();
        cout << "[" << *it << "]|";
        if (debug) cout << endl;
    }
    cout << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "test ++ operator: " << endl;
    BPlusTree<int>::Iterator it = bpt.begin();
    cout << "{" << *(it++) << "}" << endl;
    cout << "{" << *it << "}" << endl;
    for (int i = 60; i < 75; i++) {
        it = bpt.find(i);
        if (!it.is_null())
            cout << *it << " was found." << endl;
        else
            cout << i << " was not found" << endl;
    }
    cout << "====================================================================" << endl;

}

void test_insert_bplustree_auto(int tree_size, int how_many)
{
    bool verified = true;
    const int MAX = 10000;
    assert(how_many < MAX);
    BPlusTree<int> bpt;
    int a[MAX];
    int original[MAX];
    int deleted_list[MAX];

    int original_size;
    int size;
    int deleted_size = 0;

    //fill a[ ]
    for (int i = 0; i < how_many; i++) {
        a[i] = i;
    }
    //shuffle a[ ]: Put this in a function!
    for (int i = 0; i < how_many; i++) {
        int from = Random(0, how_many - 1);
        int to = Random(0, how_many - 1);
        int temp = a[to];
        a[to] = a[from];
        a[from] = temp;
    }
    //copy  a[ ] -> original[ ]:
    copy_array(original, a, original_size, how_many);
    size = how_many;
    for (int i = 0; i < size; i++) {
        bpt.insert(a[i]);
    }

    for (int i = 0; i < size; i++)
    {
        if (!bpt.contains(a[i]))
        {
            verified = false;
            break;
        }
    }
    cout << "**************************************************************************" << endl;
    cout << "**************************************************************************" << endl;
    cout << "             E N D     T E S T: " << how_many << " tests of " << tree_size << " items: ";
    cout << (verified ? "VERIFIED" : "VERIFICATION FAILED") << endl;
    cout << "**************************************************************************" << endl;
    cout << "**************************************************************************" << endl;
}

void test_bplustree_auto(int tree_size, int how_many, bool report) {
    bool verified = true;
    for (int i = 0; i < how_many; i++) {
        if (report) {
            cout << "*********************************************************" << endl;
            cout << " T E S T:    " << i << endl;
            cout << "*********************************************************" << endl;
        }
        if (!test_bplustree_auto(tree_size, report)) {
            cout << "T E S T :   [" << i << "]    F A I L E D ! ! !" << endl;
            verified = false;
            return;
        }

    }
    cout << "**************************************************************************" << endl;
    cout << "**************************************************************************" << endl;
    cout << "             E N D     T E S T: " << how_many << " tests of " << tree_size << " items: ";
    cout << (verified ? "VERIFIED" : "VERIFICATION FAILED") << endl;
    cout << "**************************************************************************" << endl;
    cout << "**************************************************************************" << endl;

}

bool test_bplustree_auto(int how_many, bool report) {
    const int MAX = 10000;
    assert(how_many < MAX);
    BPlusTree<int> bpt;
    int a[MAX];
    int original[MAX];
    int deleted_list[MAX];

    int original_size;
    int size;
    int deleted_size = 0;

    //fill a[ ]
    for (int i = 0; i < how_many; i++) {
        a[i] = i;
    }
    //shuffle a[ ]: Put this in a function!
    for (int i = 0; i < how_many; i++) {
        int from = Random(0, how_many - 1);
        int to = Random(0, how_many - 1);
        int temp = a[to];
        a[to] = a[from];
        a[from] = temp;
    }
    //copy  a[ ] -> original[ ]:
    copy_array(original, a, original_size,how_many);
    size = how_many;
    for (int i = 0; i < size; i++) {
        bpt.insert(a[i]);
    }
    if (report) {
        cout << "========================================================" << endl;
        cout << "  " << endl;
        cout << "========================================================" << endl;
        cout << bpt << endl << endl;
    }
    for (int i = 0; i < how_many; i++) {
        int r = Random(0, how_many - i - 1);
        if (report) {
            cout << "========================================================" << endl;
            cout << bpt << endl;
            cout << ". . . . . . . . . . . . . . . . . . . . . . . . . . . . " << endl;
            cout << "deleted: "; print_array(deleted_list, deleted_size);
            cout << "   from: "; print_array(original, original_size);
            cout << endl;
            cout << "  REMOVING [" << a[r] << "]" << endl;
            cout << "========================================================" << endl;
        }
        bpt.remove(a[r]);


        delete_item(a, r, size, deleted_list[deleted_size++]);
        if (!bpt.is_valid()) {
            cout << setw(6) << i << " I N V A L I D   T R E E" << endl;
            cout << "Original Array: "; print_array(original, original_size);
            cout << "Deleted Items : "; print_array(deleted_list, deleted_size);
            cout << endl << endl << bpt << endl << endl;
            return false;
        }

    }
    if (report) cout << " V A L I D    T R E E" << endl;

    return true;
}

int Random(int lo, int hi)
{
    int r = rand() % (hi - lo + 1) + lo;

    return r;
}