#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <cassert>
#include "node.h"
using namespace std;

template <typename T>
class Stack
{
public:
    class Iterator
    {
    public:
        friend class Stack;
        Iterator(){}

        Iterator(node<T>* &top):_top(top){}

        const T& operator *() const
        {
            return _top->_item;
        }

        const T* operator ->() const
        {
            assert(_top);

            return &_top->_item;
        }

        bool is_null()
        {
            return (_top == nullptr);
        }

        friend Stack<T>::Iterator operator ++(Iterator i,int unused)
        {
            assert(i._top);

            Iterator hold;
            hold = i;
            i._top = i._top->_next;
            return hold;
        }

        friend Stack<T>::Iterator operator --(Iterator i, int unused)
        {
            assert(i._top);

            Iterator hold;
            hold = i;
            i._top = i._top->_prev;
            return hold;
        }

        friend bool operator ==(const Iterator& LHS
                                , const Iterator& RHS)
        {
            if(LHS._top == RHS._top) {return true;}
            else {return false;}
        }

        friend bool operator !=(const Iterator& LHS
                                , const Iterator& RHS)
        {
            if(LHS._top == RHS._top) {return true;}
            else {return false;}
        }
    private:
        node<T>* _top;
    };

    //Default Contructor
    Stack():_top(NULL),_size(0){}

    //Big Three
    ~Stack()
    {
        _clear_list(_top);
        _size = 0;
    }
    Stack(const Stack<T>& other)
    {
        _top = nullptr;
        _copy_list(_top,other._top);
        _size = other._size;
    }
    Stack<T>& operator =(const Stack<T>& rhs)
    {
        if(&rhs == this) {return *this;}
        _clear_list(_top);
        _copy_list(_top,rhs._top);
        _size = rhs._size;
        return *this;
    }

    //Primary Function
    void push(const T& item)
    {
        _insert_head(_top,item);
        _size++;
    }
    T pop()
    {
        if(_size > 0)
        {
            T hold = _remove_head(_top);
            _size--;
            return hold;
        }
        else
        {
            return T();
        }
    }
    T top()
    {
        T hold = _at(_top,0);
        return hold;
    }
    int size() const
    {
        return _size;
    }
    bool empty()
    {
        if(_size <= 0) {return true;}
        else {return false;}
    }
    void clear()
    {
        _clear_list(_top);
        _size = 0;
    }

    //Iterator dependent Functions
    typename Stack<T>::Iterator Begin()
    {
        return Iterator(_top);
    }
    typename Stack<T>::Iterator End() const
    {
        return Iterator(_last_node(_top));
    }

    //Print Function
    friend ostream& operator <<(ostream& outs, const Stack& s)
    {
        return _print_list(s._top, outs);
    }
private:
    node<T>* _top;
    int _size;
};

void test_stack_function()
{
    cout << endl << endl << "Begin Stack Test Function\n\n\n";
    Stack<int> s1;
    cout << "Initializing 2 stacks...\n";
    for(int i=0; i < 10; i++)
    {
        s1.push(i);
    }
    Stack<int> s2(s1);
    cout << "Displaying Stacks: \n";
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;

    while(!s2.empty())
    {
        cout << "{" << s2.pop() << "}" << " " << s2 << endl;
    }

    cout << "Assigning s1 back to s2: " << endl;
    s2 = s1;
    cout << "s2: " << s2 << endl;

    cout << "Completed Stack Testing\n\n";
}



























#endif // STACK_H
