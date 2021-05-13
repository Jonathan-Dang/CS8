#pragma once
#include <iostream>
#include <vector>
using namespace std;

//--------------------------------------------------------------------------//
//                             BTREE FUNCTION CALLS                         //
//--------------------------------------------------------------------------//

template <class T>
T maximal(const T& a, const T& b);                      //return the larger of the two items

template <class T>
void swap(T& a, T& b);  //swap the two items

template <class T>
int index_of_maximal(T data[], int size);                 //return index of the largest item in data

template <class T>
void ordered_insert(T data[], int& size, T entry);        //insert entry into the sorted array
                                                        //data with length n [Shift Right]

template <class T>
int first_ge(const T data[], int size, const T& entry);   //return the first element in data that is
                                                        //not less than entry

template <class T>
void attach_item(T data[], int& size, const T& entry);    //append entry to the right of data [Push Back]

template <class T>
void insert_item(T data[], int i, int& size, T entry);    //insert entry at index i in data [Shift right]

template <class T>
void detach_item(T data[], int& size, T& entry);          //remove the last element in data and place
                                                        //it in entry [Shift Left]

template <class T>
void delete_item(T data[], int i, int& size, T& entry);   //delete item at index i and place it in entry

template <class T>
void merge(T data1[], int& size1, T data2[], int& size2);   //append data2 to the right of data1

template <class T>
void split(T data1[], int& size1, T data2[], int& size2);   //move n/2 elements from the right of data1
                                                        //and move to data2

template <class T>
void copy_array(T dest[], const T src[],
    int& dest_size, int src_size);              //copy src[] into dest[]

template <class T>
void print_array(const T data[], int size, int pos = -1);  //print array data

template <class T>
bool is_gt(const T data[], int size, const T& item);       //item > all data[i]

template <class T>
bool is_le(const T data[], int size, const T& item);       //item <= all data[i]

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list); //print vector list

template <typename T, typename E>
vector<T>& operator +=(vector<T>& list, const E& addme); //list.push_back addme

template <typename T>
vector<T> Union(const vector<T>& lhs, const vector<T>& rhs);

template <typename T>
vector<T> Intersection(const vector<T>& lhs, const vector<T>& rhs);

//--------------------------------------------------------------------------//
//                        BTREE FUNCTION DEFINITIONS                        //
//--------------------------------------------------------------------------//

template<class T>
inline T maximal(const T& a, const T& b)
{
    if (a > b)
        return a;
    else
        return b;
}

template<class T>
inline void swap(T& a, T& b)
{
    T hold = a;
    a = b;
    b = hold;
}

template<class T>
inline int index_of_maximal(T data[], int size)
{
    T max = data[0];

    for (int i = 0; i < size; i++)
    {
        if (max < data[i])
            max = data[i];
    }

    for (int i = 0; i < size; i++)
    {
        if (max == data[i])
            return i;
    }
    return NULL;
}

template<class T>
inline void ordered_insert(T data[], int& size, T entry)
{
    for (int i = 0; i < size; i++)
    {
        if (entry < data[i])
        {
            size++;
            for (int t = size - 1; t > i; t--)
            {
                data[t] = data[t - 1];
            }
            data[i] = entry;
            break;
        }
    }
}

template<class T>
inline int first_ge(const T data[], int size, const T& entry)
{
    int pos = 0;
    if (size == 0)
        return 0;

    for (int i = 0; i < size; i++)
    {
        if (entry > data[i])
            pos++;
    }
    return pos;
}

template<class T>
inline void attach_item(T data[], int& size, const T& entry)
{
    data[size] = entry;
    size++;
}

template<class T>
inline void insert_item(T data[], int i, int& size, T entry)
{
    size++;
    for (int t = size - 1; t > i; t--)
    {
        data[t] = data[t - 1];
    }
    data[i] = entry;
}

template<class T>
inline void detach_item(T data[], int& size, T& entry)
{
    entry = data[size - 1];
    data[size - 1] = T();
    size--;
}

template<class T>
inline void delete_item(T data[], int i, int& size, T& entry)
{
    entry = data[i];
    for (int t = i; t < size; t++)
    {
        data[t] = data[t + 1];
    }
    size--;
}

template<class T>
inline void merge(T data1[], int& size1, T data2[], int& size2)
{
    for (int i = 0; i < size2; i++)
    {
        attach_item(data1, size1, data2[i]);
    }
    size2 = 0;
}

template<class T>
inline void split(T data1[], int& size1, T data2[], int& size2)
{
    int true_size = size1 / 2;
    size2 = true_size;
    int pos = 0;
    for (int i = size1 - true_size; i < size1; i++)
    {
        data2[pos] = data1[i];
        pos++;
    }
    size1 -= true_size;
}

template<class T>
inline void copy_array(T dest[], const T src[], int& dest_size, int src_size)
{
    for (int i = 0; i < src_size; i++)
    {
        dest[i] = src[i];
    }
    dest_size = src_size;
}

template<class T>
inline void print_array(const T data[], int size, int pos)
{
    if (pos == -1)
        pos = 0;
    for (int i = pos; i < size; i++)
    {
        cout << data[i] << " ";
    }
    cout << endl;
}

template<class T>
inline bool is_gt(const T data[], int size, const T& item)
{
    for (int i = 0; i < size; i++)
    {
        if (item <= data[i])
            return false;
    }
    return true;
}

template<class T>
inline bool is_le(const T data[], int size, const T& item)
{
    for (int i = 0; i < size; i++)
    {
        if (item > data[i])
            return false;
    }
    return true;
}

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list)
{
    for (int i = 0; i < list.size(); i ++)
    {
        outs << list[i];
        if (i != list.size() - 1)
            outs << ", ";
    }
    return outs;
}

template <typename T, typename E>
vector<T>& operator +=(vector<T>& list, const E& addme)
{
    list.push_back(addme);
    return list;
}

template <typename T>
vector<T> Union(const vector<T>& lhs, const vector<T>& rhs)
{
    vector<T> unionV;
    int lhs_pos = 0, rhs_pos = 0;
    while (lhs_pos < lhs.size() && rhs_pos < rhs.size())
    {
        if (lhs[lhs_pos] < rhs[rhs_pos])
        {
            unionV.push_back(lhs[lhs_pos]);
            lhs_pos++;
        }
        else if (lhs[lhs_pos] > rhs[rhs_pos])
        {
            unionV.push_back(rhs[rhs_pos]);
            rhs_pos++;
        }
        else
        {
            unionV.push_back(lhs[lhs_pos]);
            lhs_pos++;
            rhs_pos++;
        }
    }

    while (rhs_pos < rhs.size())
    {
        unionV.push_back(rhs[rhs_pos]);
        rhs_pos++;
    }
    while (lhs_pos < lhs.size())
    {
        unionV.push_back(lhs[lhs_pos]);
        lhs_pos++;
    }

    return unionV;
}

template <typename T>
vector<T> Intersection(const vector<T>& lhs, const vector<T>& rhs)
{
    vector<T> interV;
    int lhs_pos = 0, rhs_pos = 0;
    while (lhs_pos < lhs.size() && rhs_pos < rhs.size())
    {
        if (lhs[lhs_pos] < rhs[rhs_pos])
            lhs_pos++;
        else if (lhs[lhs_pos] > rhs[rhs_pos])
            rhs_pos++;
        else
        {
            interV.push_back(lhs[lhs_pos]);
            lhs_pos++;
            rhs_pos++;
        }
    }
    return interV;
}