#include <iostream>
#include <vector>
using namespace std;

class Base
{
public:
    virtual void f()
    {
        cout<< "Base::f()" <<endl;
    }

    virtual void t()
    {
        cout<< "Base::t()"<<endl;
    }

    void y()
    {
        cout<< "Base::y()"<<endl;
    }
};

class Derive
:public Base
{
public:
    void f()
    {
        cout<< "Derive::f()"<<endl;
    }

    virtual void t(int a)
    {
        cout<< "Derive::t()"<<endl;
    }

    void y(int a)
    {
        cout<< "Derive::y()"<<endl;
    }
};

int main()
{
    Base* b = new Derive();
    Derive* d = (Derive*)b;

    b->f();

    b->t();

    //b->y();
    //b->y(1); //erro
    
    d->y(1);
    d->Base::y();

    return 0;
}

