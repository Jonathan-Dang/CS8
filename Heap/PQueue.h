#pragma once
#include "Heap.h"
#include <iostream>
using namespace std;

template <typename T>
struct info {
    T _item;
    int _priority;
    int _serial_number;

    info() :_item(T()), _priority(0), _serial_number(0) {}
    info(T i, int p, int s) :_item(i), _priority(p), _serial_number(s) {}

    friend ostream& operator <<(ostream& outs, const info<T>& print_me)
    {
        outs << print_me._item;
        return outs;
    }

    friend bool operator <(const info<T>& lhs, const info<T>& rhs)
    {
        if(lhs._priority != rhs._priority)
            return lhs._priority < rhs._priority;
        else
            return lhs._serial_number < rhs._priority;
    }

    friend bool operator <=(const info<T>& lhs, const info<T>& rhs)
    {
        if (lhs._priority != rhs._priority)
            return lhs._priority <= rhs._priority;
        else
            return lhs._serial_number <= rhs._priority;
    }

    friend bool operator >(const info<T>& lhs, const info<T>& rhs)
    {
        if (lhs._priority != rhs._priority)
            return lhs._priority > rhs._priority;
        else
            return lhs._serial_number > rhs._priority;
    }

    friend bool operator >=(const info<T>& lhs, const info<T>& rhs)
    {
        if (lhs._priority != rhs._priority)
            return lhs._priority >= rhs._priority;
        else
            return lhs._serial_number >= rhs._priority;
    }

    friend bool operator ==(const info<T>& lhs, const info<T>& rhs)
    {
        return (lhs._item == rhs._item);
    }
};

template <typename T>
class PQueue
{
public:
    PQueue();

    bool insert(const T& value, int p, int s);
    info<T> Pop();

    bool is_empty() const;
    int size() const;
    void print_tree() const;
    friend ostream& operator <<(ostream& outs, const PQueue<T>& print_me)
    {
        print_me.print_tree();  
        return outs;
    }

private:
    Heap<info<T>> heap;

};

template<typename T>
inline PQueue<T>::PQueue()
{
    //left intensionally blank
}

template<typename T>
inline bool PQueue<T>::insert(const T& value, int p, int s)
{    
    heap.insert(info<T>(value, p, s));
    return true;
}

template<typename T>
inline info<T> PQueue<T>::Pop()
{
    return heap.Pop();
}

template<typename T>
inline bool PQueue<T>::is_empty() const
{
    return heap.is_empty();
}

template<typename T>
inline int PQueue<T>::size() const
{
    return heap.size();
}

template<typename T>
inline void PQueue<T>::print_tree() const
{
    cout << heap << endl;
}
