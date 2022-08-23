#include <iostream>
using namespace std;

// 不使用变量交换整型数
void t()
{
    int a = 1;
    int b = 2;

    a = a^b;
    b = a^b;
    a = a^b;

    cout<< a <<endl;
    cout<< b <<endl;
}

int main()
{
    t();
    return 0;
}

