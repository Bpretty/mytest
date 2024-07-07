#include <iostream>
using namespace std;

class Base
{
public:
    virtual void func()
    {
        cout<< "i am Base::func()" << endl;
    }
private:
    int a;
};

class Derive:public Base
{
public:
    void func() 
    {
        cout<< "i am Derive::func()" << endl;
    }
private:
    int b;
};

struct A
{
    void print()
    {
        cout<< "A::print()"<<endl;
    };
};

struct B:A
{
    void print()
    {
        cout<< "B::print()"<<endl;
    };
};
int main()
{
#if 0
    Base* b = new Derive();
    b->func();
#endif

    B x;
    x.print();

    return 0;
}

