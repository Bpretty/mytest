#include <iostream>
using namespace std;

class A
{
public:
    int f()
    {
        cout<<"f()"<<endl;
    }

    virtual void t()
    {
        cout<< "base::t()"<<endl;
    }
};

class B
:public A
{
    int f(int a)
    {
        cout<<"f(int)"<<endl;
    }

    virtual void t()
    {
        cout<< "Derive::t()"<<endl;
        //return 1;
    }
};


int main()
{
    B b1;
    b1.A::f();
    //b1.f(); //erro

    return 0;
}

