#include <iostream>
using namespace std;
// 测试const变量初始化

class Demo
{
public:
    Demo()
    //:a(-1)
    //,b(-2)
    {}

public:
    // const 变量声明的时候是可以初始化的
    const int a = 2;
    int b = 3;
};

int main()
{
    Demo d;
    cout << d.a<<endl;
    cout << d.b<<endl;

    return 0;
}

