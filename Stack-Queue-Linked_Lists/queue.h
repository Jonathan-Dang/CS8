#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include "node.h"
using namespace std;

template <typename T>
class Queue
{
public:

    class Iterator {
    public:
        friend class Queue;
        Iterator(){}

        Iterator(node<T>* top = nullptr
                ,node<T>* bot = nullptr):_top(top),_bot(bot){}

        const T& operator *() const
        {
            assert(_top);
            return _top->_item;
        }

        T* operator->()
        {
            assert(_top);
            return &(_top->_item);
        }

        const node<T>* operator ->() const
        {
            assert(_top);
            return &(_top->_item);
        }
        friend Queue<T>::Iterator operator ++(Iterator i,int unused)
        {
            assert(i._top);

            Iterator hold;
            hold = i;
            i._top = i._top->_next;
            return hold;
        }
        friend Queue<T>::Iterator operator --(Iterator i, int unused)
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
        node<T>* _bot;
    };

    //Default Constructor
    Queue():_top(nullptr),_bot(nullptr),_size(0){}

    //Big 3
    ~Queue()
    {
        _clear_list(_top);
        _top = nullptr;
        _bot = nullptr;
        _size = 0;
    }
    Queue(const Queue<T>& other)
    {
        _top = nullptr;
        _bot = _copy_list(_top,other._top);
        _size = other._size;
    }
    Queue<T>& operator =(const Queue<T>& rhs)
    {
        if(this == &rhs) {return *this;}
        _clear_list(_top);
        _bot = _copy_list(_top,rhs._top);
        _size = rhs._size;
        return *this;
    }

    //Primary Function
    void push(const T& item)
    {
        _bot = _insert_after(_top,_bot,item);
        _size++;
    }
    void clear()
    {
        _clear_list(_top);
        _bot = nullptr;
        _size = 0;
    }
    T pop()
    {
        if(_size > 0)
        {
            _size--;
            return _remove_head(_top);
        }
        else
        {
            return T();
        }

    }
    T front() const
    {
        return _top->_item;
    }
    T back() const
    {
        return _bot->_item;
    }
    int size() const
    {
        return _size;
    }
    bool empty() const
    {
        if(_size <= 0) {return true;}
        else {return false;}
    }

    //Iterator dependent Functions
    typename Queue<T>::Iterator Begin()
    {
        return Iterator(_top);
    }
    typename Queue<T>::Iterator End()
    {
        return Iterator(_bot);
    }

    //Print Function
    friend ostream& operator <<(ostream& outs, const Queue& q)
    {
        return _print_list(q._top,outs);
    }
private:
    node<T>* _top; //Exit
    node<T>* _bot; //Enterence
    int _size;
};


void test_queue_function()
{
    Queue<int> q1;
    cout << endl << endl << "Begining Queue Testing\n\n";
    for(int i = 0; i < 10; i++)
    {
        q1.push(i);
    }
    Queue<int> q2(q1);
    cout << "Initialized 2 queues...\n\n";
    cout << "Displaying Queues\n";
    cout << "q1: " << q1 << endl << "q2: " << q2 << endl;

    while(!q2.empty())
    {
        cout << "{" << q2.pop() << "}" << " " << q2 << endl;
    }

    cout << "Assigning q1 back to q2: " << endl;
    q2 = q1;
    cout << "q2: " << q2 << endl;

    cout << "Completed Queue Testing\n\n";
}



#endif // QUEUE_H
