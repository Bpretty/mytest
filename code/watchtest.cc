#include <stdio.h>

#include <iostream>
using namespace std;

void test0()
{
    bool b = true;
    cout<< b <<endl;
    b = false;
    cout<< b <<endl;


}

void test1()
{
    char buf[128] = {0};
    cout << "print buf: "<<buf<<endl;

    buf[0] = 'h';
    buf[1] = 'e';
    buf[2] = 'l';
    buf[3] = 'l';
    buf[4] = 'o';

    cout << "print buf: "<<buf<<endl;
}

int main()
{
    test0();

    test1();


    return 0;
}

