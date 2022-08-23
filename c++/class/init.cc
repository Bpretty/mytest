#include <iostream>
using namespace std;

// 测试类成员的初始化

class A
{
public:
    A()
    {
        cout<< "A()"<<endl;
    }
};

class B
{
public:
    B()
    {
        cout<<"B()"<<endl;
    }
private:
    A _a;
    int _b;
};

int main()
{
    B b;

    return 0;
}

