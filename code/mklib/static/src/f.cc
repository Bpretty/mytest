#include <iostream>

#include "../inc/f.h"
using std::cout;
using std::endl;

int add(int a, int b)
{
    int sum = a + b;
    cout << "sum = "<< sum << endl;

    return sum;
}

int sub(int a, int b)
{
    int sum = a - b;
    cout << "sub = "<< sum << endl;

    return sum;
}
