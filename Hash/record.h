#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct record
{
    int _key;
    T _value;

    record(int key = -1, T value = T()) :_key(key), _value(value) {}

    friend bool operator ==(const record& left, const record& right)
    {
        return left._key == right._key;
    }
    friend bool operator <(const record& left, const record& right)
    {
        return left._key < right._key;
    }
    friend bool operator >(const record& left, const record& right)
    {
        return left._key > right._key;
    }

    friend ostream& operator <<(ostream& outs, const record& print_me)
    {
        outs << "[" << print_me._key << "|" << print_me._value << "]";
        return outs;
    }
    friend istream& operator >>(istream& ins, record& insert)
    {
        char throwaway;
        ins >> insert._key >> throwaway >> insert._value;
        return ins;
    }
};