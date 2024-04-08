#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print( int i)
{
    cout<< i<<endl;
}

void (* Pointer)(int) = print;

typedef void (*FuncCallBack)(int);

void test0()
{
    FuncCallBack func = print;
    func(1);
}

int main()
{
    test0();

    return 0;
}

