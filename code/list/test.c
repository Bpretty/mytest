#include <stdio.h>

void t(int* p)
{
    int a = 5;

    *p += a;
}

void test()
{
    while(1);
}

int main()
{
    int a = 0;
    t(&a);

    test();

    return 0;
}

