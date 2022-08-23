#include <iostream>
using namespace std;
// 测试空间大小

class Demo1
{
public:
    virtual void func()
    {}

public:
    short a;
    int b;
    int c;
};

void t1()
{ 
    Demo1 d;
    cout << sizeof(d) <<endl;
    cout<< sizeof(Demo1) <<endl;
}

class Demo2
{
public:
    char a;
    double c;
    int b;
    char d;
};

void t2()
{
    cout<< sizeof(Demo2);
}

class Demo3
{
public:
    char a;
    int c;
    int b;
    char d;
    int e;

    // 4字节对齐应该是20,8字节对齐应该是24
    // 结果为 20,故，此处按照其最大类型即4字节对齐
};

void t3()
{
    cout<< sizeof(Demo3);
}

class Demo4
{
    char a;
    short b;
    short c;
};

void t4()
{
    cout<< sizeof(Demo4)<<endl;
}

class Demo5
{
    int b;
    double c;
};

void t5()
{
    cout<< sizeof(Demo5)<<endl;
}

class S3
{
    int b;
    char a;
    //int b;
};

class S4
{
    char a;
    S3 b;   // 注意类成员另起一个重新对齐的位置计算
    char c;
};//16

void t6()
{
    cout<< sizeof(S4)<<endl;
}


int main()
{
    //t2();
    //t3();
    //t4();
    //t5();
    t6();

    return 0;
}
