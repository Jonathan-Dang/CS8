#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cassert>
using namespace std;

template <typename T>
struct node{
  T _item;
  node<T>* _next;
  node<T>* _prev;

  node(const T& item=T(), node<T>* next = nullptr, node<T>* prev = nullptr):
                    _item(item), _next(next), _prev(prev){}

    friend ostream& operator<<(ostream& outs, const node<T>* n)
    {
        outs<<n->_item;
        return outs;
    }
};

//===========================================================================//
//                            NODE FUNCTION CALLS                            //
//===========================================================================//

template<typename T>
node<T>* _insert_head(node<T>*& head_ptr, const T& item); //Done

template<typename T>
ostream& _print_list(node<T>* head_ptr, ostream& outs = cout); //Done

template <typename T>
T _remove_node(node<T>*& head, node<T>* deleteThis); //Done

template <typename T>
node<T>* _previous_node(node<T>* head, node<T>* prevToThis); //Done

template <typename T>
T _remove_head(node<T>*& headptr); //Done

template <typename T>
node<T>* _search_list(node<T>* head, T key); //Done

template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *afterThis, T insertThis); //Done

template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* beforeThis, T insertThis); //Done

template <typename T>
void _clear_list(node<T>*& head); //Done

template <typename T>
node<T>* _copy_list(node<T>*& dest, node<T>* src); //Done

template <typename T>
T& _at(node<T>* head, int pos); //Done

//===========================================================================//
//                         SORTED LIST FUNCTION CALLS                        //
//===========================================================================//
template <typename T>
node<T>* _last_node(node<T>* head); //Done

template <typename T>
node<T>* _where_this_goes(node<T>* head, T item, bool ascending=true); //Done

template <typename T>
node<T>* _insert_sorted(node<T>* &head, T item, bool ascending=true);

//===========================================================================//


//===========================================================================//
//                         NODE FUNCTION DEFINITIONS                         //
//===========================================================================//

template<typename T>
node<T>* _insert_head(node<T>*& head_ptr, const T& item)
{
    if(head_ptr == nullptr)
    {
        node<T>* temp = new node<T>(item);
        temp->_next = head_ptr;
        head_ptr = temp;

        return head_ptr;
    }
    else
    {
        node<T>* temp = new node<T>(item);
        temp->_next = head_ptr;
        head_ptr->_prev = temp;
        head_ptr = temp;

        return head_ptr;
    }
}

template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *afterThis, T insertThis)
{
    node<T>* w = head;
    while(w != afterThis) {w = w->_next;}

    if(w == nullptr)
    {
        return _insert_head(head,insertThis);
    }

    node<T>* newnode = new node<T>(insertThis);
    if(w->_next == nullptr)
    {
        newnode->_next = nullptr;
    }
    else
    {
        newnode->_next = w->_next;
    }
    newnode->_prev = afterThis;
    w->_next = newnode;

    return newnode;
}

template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* beforeThis, T insertThis)
{
    node<T>* w = head;
    while(w->_next != beforeThis) {w = w->_next;}

    if(w == nullptr)
    {
        return _insert_head(head,insertThis);
    }

    node<T>* newnode = new node<T>(insertThis);

    newnode->_next = w->_next;
    newnode->_prev = w;
    w->_next = newnode;

    return newnode;
}

template <typename T>
node<T>* _search_list(node<T>* head, T key)
{
    node<T>* w = head;
    while(w->_next != nullptr)
    {
        if(w->_item == key) {return w;}
        w = w->_next;
    }

    return nullptr;
}

template<typename T>
ostream& _print_list(node<T>* head_ptr, ostream& outs)
{
    outs<<"H->";
    if(head_ptr != nullptr)
    {
        for(node<T>* w = head_ptr; w != nullptr; w=w->_next)
        {
            outs<<"["<<w<<"]->";
        }
    }
    outs<<"|||\n";
    return outs;
}

template <typename T>
node<T>* _previous_node(node<T>* head, node<T>* prevToThis)
{
    node<T>* w = head;
    while(w->_next != prevToThis) {w = w->_next;}
    return w;
}

template <typename T>
T _remove_node(node<T>*& head, node<T>* deleteThis)
{
    assert(head != nullptr && "EMPTY NODE");
    if(deleteThis == head) {return _remove_head(head);}

    node<T>* w = deleteThis;
    (_previous_node(head,deleteThis))->_next = w->_next;
    T hold = w->_item;
    _remove_head(w);

    return hold;
}

template <typename T>
T _remove_head(node<T>*& headptr)
{
    assert(headptr != nullptr && "EMPTY NODE");

    if(headptr->_next == nullptr)
    {
        T hold = headptr->_item;
        headptr = nullptr;
        return hold;
    }

    node<T>* w = headptr->_next;
    T hold = headptr->_item;
    delete headptr;
    headptr = w;
    headptr->_prev = nullptr;

    return hold;
}

template <typename T>
T& _at(node<T>* head, int pos)
{
    node<T>* w = head;
    for(int i = 0; i <= pos-1; i++)
    {
        assert(w != nullptr && "NO CONTENT");
        w = w->_next;
    }
    return w->_item;
}

template <typename T>
void _clear_list(node<T>*& head)
{
    while(head != nullptr)
    {
        _remove_head(head);
    }
}

template <typename T>
node<T>* _copy_list(node<T>*& dest, node<T>* src) //return last node instead!
{
    node<T>* wDest = dest;
    node<T>* wSrc = src;
    while(wSrc != nullptr)
    {
        wDest = _insert_after(dest,wDest,wSrc->_item);
        wSrc = wSrc->_next;
    }
    return wDest;
}

//---------------------------------------------------------------------------//
//                        SORTED LIST FUNCTIONS (nodes)                      //
//---------------------------------------------------------------------------//
template <typename T>
node<T>* _last_node(node<T>* head)
{
    node<T>* w = head;
    if(w)
    {
        while(w->_next != nullptr) {w = w->_next;}
    }
    return w;
}

template <typename T>
node<T>* _where_this_goes(node<T>* head, T item, bool ascending)
{
    if(head == nullptr)
    {
        return head;
    }

    node<T>* w = head;
    node<T>* w2 = head->_next;

    while(w2 != nullptr)
    {
        if(ascending)
        {
            if(item < w2->_item)
            {
                return w;
            }
            w = w->_next;
            w2 = w2->_next;
        }
        else
        {
            if(item > w2->_item)
            {
                return w;
            }
            w = w->_next;
            w2 = w2->_next;
        }
    }
    return w;
}

template <typename T>
node<T>* _insert_sorted(node<T>* &head, T item, bool ascending)
{
    node<T>* w = _where_this_goes(head,item,ascending);
    if(w == nullptr)
    {
        return _insert_head(head,item);
    }

    if(ascending)
    {
        return _insert_after(head,w,item);
    }
    else
    {
        return _insert_after(head,w,item);
    }
}

//---------------------------------------------------------------------------//
//                           TESTING NODE FUNCTIONS                          //
//---------------------------------------------------------------------------//

void _test_node()
{
    cout << endl << endl << "TESTING SINGLE NODE FUNCTIONS\n";

    node<int>* head_ptr=nullptr;
    cout << endl << "Initializing node list: \n";
    for (int i=0; i<10; i++)
    {
        _insert_head(head_ptr, i*10);
        _print_list(head_ptr);
        cout<<endl;
    }
    cout << "Initial Node List: \n";
    _print_list(head_ptr);
    cout << endl;

    cout << "Insert After 30: \n";
    _insert_after(head_ptr,_search_list(head_ptr,30),69420);
    _print_list(head_ptr);
    cout<<endl;
    cout << "Insert Before 40: \n";
    _insert_before(head_ptr,_search_list(head_ptr,40),69420);
    _print_list(head_ptr);
    cout<<endl;
    cout << "DELETED NODE: "<< _remove_node(head_ptr,_search_list(head_ptr,40)) << endl;
    _print_list(head_ptr);
    cout<<endl;
    cout << "DELETED HEAD: "<< _remove_head(head_ptr) << endl;
    _print_list(head_ptr);
    cout<<endl;
    cout << "~DELETED THE ENTIRE LIST~\n";
    _clear_list(head_ptr);
    _print_list(head_ptr);
    for (int i=0; i<10; i++)
    {
        _insert_head(head_ptr, i*10);
    }
    cout << endl;
    cout << "~COPYING THE ENTIRE LIST~\n";
    node<int>* Hptr = nullptr;
    _copy_list(Hptr,head_ptr);
    cout << "Initial List: \n";
    _print_list(head_ptr);
    cout << endl;
    cout << "Copied List: \n";
    _print_list(Hptr);
    cout << endl;
    cout << "Target value held in position 4 is: \n";
    cout << _at(head_ptr,4) << endl;
    cout << endl << endl;

    cout << "Initial List: \n";
    _print_list(head_ptr);
    node<int>* w = _where_this_goes(head_ptr,55,false);
    cout << endl << "Insert after: " <<w->_item << " for value 55."<< endl;
    cout << "Inputing value 55 into the list: \n";
    _insert_sorted(head_ptr,55,false);
    _print_list(head_ptr);

    cout << endl << endl << "COMPLETED NODE TESTING\n";
}


#endif // NODE_H
