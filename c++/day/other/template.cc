#include <iostream>
using namespace std;

template<class T>
T add(T x, T y)
{
    return x+y;
}

// 函数模板也可以以成员函数的形式定义，普通类中


class E
{
public:
    E(){}

    template<class T>
    T print(T x)
    {
        cout<< x <<endl;
    }
private:
    int _a;
};


void t1()
{
    E e;
    e.print<int>(1);
    e.print<double>(2.2);
}

int main()
{
    t1();

    return 0;
}

