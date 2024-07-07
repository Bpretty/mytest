#include <stdio.h>

int func(int a)
{
    printf("%d\n", a);
}

typedef int (*callback)(int);

void t()
{
    int (*p)(int) = func;
    callback p1 = func;

    p(10);
    p1(11);
}

int main()
{
    t();

    return 0;
}

