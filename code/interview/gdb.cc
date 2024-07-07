#include <iostream>
#include <vector>
using namespace std;

void t1(int & b)
{
    int a = 1;
    for(; a < 10; a++)
    {
        cout<< a <<endl;
    }

    b = 1;
}

int main()
{
    int a = 0;
    t1(a);
    int c = 1;
    int d = 2;
    c = 1;
    c = 2;

    return 0;
}

