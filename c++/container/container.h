#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

template<class T>
void print( const T& t )
{
    typename T::const_iterator beg = t.cbegin();
    for(; beg != t.cend(); beg++)
    {
        cout<< *beg <<endl;
    }
}

template<class T>
void forprint(const T& t)
{
    for(auto& e : t)
    {
        cout<< e <<endl;
    }
}
