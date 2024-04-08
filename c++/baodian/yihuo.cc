#include <iostream>
using namespace std;

void t()
{
    int a = 1;
    int b = 2;

    a = a^b;
    b = a^b;
    a = a^b;

    cout << a <<endl;
    cout << b <<endl;
}

int main()
{
    t();

    return 0;
}

