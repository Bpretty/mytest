#include <iostream>
#include <vector>
using namespace std;

template<class T>
void print(const T& x)
{
    //typename T::const_iterator it = x.begin();
    class T::const_iterator it = x.begin();
    for(; it != x.end(); it++)
    {
        cout<< *it <<endl;
    }
}

void t()
{
    vector<int> v{1,2,3};

    vector<int>::iterator beg = v.begin();
    for( ; beg != v.end(); beg++)
    {
        cout<< *beg <<endl;
    }
}

struct A
{
    typedef int type_A ;

    int _a;
};

void t2()
{
    A::type_A a;
}


void t3()
{
    vector<int> v{5,4,3,2,1};

    print(v);
}

int main()
{
    t3();
    return 0;
}

