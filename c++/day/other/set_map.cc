#include <iostream>
#include <set>
#include <map>
using namespace std;

template<class T>
void display(T& c)
{
    typename T::iterator it = c.begin();

    for(; it != c.end(); it++)
    {
        cout<< *it <<endl;
    }
}


void t()
{
    set<int> numbers{6,2,3,9,5,4,2,1};

    //display(numbers);

    set<int>::iterator it = numbers.begin();
    auto end = ++it;
    ++end;
    set<int> a( it, end );
    display(a);

    // 添加新元素
    std::pair< set<int>::iterator, bool > ret =  numbers.insert(20);
    if (ret.second)
    {
        cout<< "success"<<endl;
        cout<< *ret.first <<endl;
    }else{
        cout<< "erro" <<endl;
    }
}

int main()
{
    t();

    return 0;
}

