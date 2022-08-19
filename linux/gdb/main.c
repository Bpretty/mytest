#include <stdio.h>

void t()
{
    for(int i = 0;i < 3; i++)
    {
        printf("i\n");
    }
}

void t1()
{
    int a = 1;
    int b = a/0;

    printf("b\n");
}

int main()
{
    int a = 1;
    int b = 1;
    int arr[3] = {1,2,3};

    t1();
    t();

    return 0;
}

