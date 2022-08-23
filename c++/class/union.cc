#include <iostream>
using namespace std;

union {
    char b[9];
    int c[2];
}u; // 12，也要考虑对齐问题

void t1()
{
    cout<< sizeof(u) <<endl;
}

int main()
{
    t1();

    return 0;
}

