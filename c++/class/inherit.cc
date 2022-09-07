#include <iostream>
using namespace std;

/*
 *protected继承和private继承：
    采用protected继承，不论层次有多少层，都能访问到最顶层基类的非私有成员
    只要某一层次采用private继承，其后的派生类都无法在访问基类的非私有成员

 */

class A
{
public:
    int _a;
protected:
    int _b;
private:
    int _c;
};

class B
:protected A
{

};

class C
:private B
{
public:
    void print()
    {
        _a = 1;
        _b = 2;
        //_c = 3;   // erro
        cout<< _b <<endl;
    }
};

class D
:public C
{
public:
    void print()
    {
        //因为基类的私有继承，继承层次被打断
        //_c = 3;
        //cout<< _c <<endl;;
    }
};

void test0()
{
    C c;
    c.print();
}


int main()
{
    test0();

    return 0;
}

