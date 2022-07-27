#include <stdio.h>

long int fun()
{
    int a = 1;
    int sum = 0;

    while(a<=100000000)
    {
        sum += a;
        a++;
    }

    return sum;
}

int main( int args, char* argv[] )
{

    //printf("hello liangting\n" );

    printf("%s, %s\n", argv[1], argv[2]);

    //printf("累计和为:%ld\n", fun());

    return 0;
}


