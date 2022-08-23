#include <iostream>
using namespace std;

void t()
{
    int a = 1;
    int b = 2;

    int a1 = a^a;
    int b1 = b^b;

    cout << a1 <<endl;
    cout << b1 <<endl;
}

int main()
{
    t();

    return 0;
}

