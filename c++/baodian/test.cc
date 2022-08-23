#include <stdio.h>
#include <iostream>

using namespace std;

void t1()
{
    int a[6] = {1,2,3,4,5,6};

    int (&b)[6] = a;    // 使用gcc编译不通过，但是g++编译通过
    //int *b = a;

    for(int i = 0;i< 6; i++ )
    {
        printf("%d\n", b[i]);
    }
}

void t2()
{
    const char* p1 = "abc";

    const char* p2 = p1;

    cout<<p2[0]<<endl;
    cout<<p2[1]<<endl;
    cout<<p2[2]<<endl;
}

void t3()
{
    //char ch[5] = "hello";   //erro 数组长度不足

    char ch[2] = {'a', '\0'};

    if (!ch[1]) cout<< "0"<<endl;

    char ch1[5] = { 'a', 'b', 'c', 'd','\0'};
    cout<< ch1<<endl;
    ch1[1] = 0;
    cout<< ch1<<endl;
}

void p(int a[])
{
    cout<< sizeof(a)<<endl;
}

void t4()
{
    int a[3] = {0};

    cout << sizeof(a)<<endl;
    p(a);
}

void t5()
{
    unsigned int a = 1;
    cout<< a*-2 <<endl;
}

int main()
{
    //t1();
    //t2();
    //t3();
    //t4();
    t5();

    return 0;
}

