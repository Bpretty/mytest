//派生类对象之间复制的时候，如果没有显示调用基类的构造函数，那么调用的是基类的默认构造函数
//使用派生类对象给基类对象初始化的时候调用的是基类的复制构造函数（不是很理解）

#include<iostream>
using namespace std;

class Base
{
public:
    Base() 
    {
        cout<< "Base()"<<endl;
    }

    Base(const Base& base)
    {
        cout<< "Base(const Base&)" <<endl;
    }

    Base& operator=(const Base& b)
    {
        cout<<"Base::operator=()"<<endl;
        return *this;
    }

    ~Base() {}
private:

};

class Derive
:public Base
{
public:
    Derive()
    {
        cout<< "Derive()"<<endl;
    }

#if 0
    Derive(const Derive& d)
    :Base(d)
    {
        cout<< "Derive(const Derive&)" <<endl;
    }
#endif

#if 1
    Derive& operator=(const Derive& d)
    {
        if (this != &d)
        {
            Base::operator=(d);
        }
        cout<< "Derive::operator=()"<<endl;

        return *this;
    }
#endif

    ~Derive() {}
};


int main()
{
    Derive d, d2;
#if 0
    Base b = d;
#endif

#if 0
    Derive d1 = d;
#endif

    d = d2;
}
