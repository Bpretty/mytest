#include <stdio.h>

int strtlen1( char* p)
{
    int len = 0;
    while( *p++ ) len++;

    return len;
}

int main()
{
    char p[] = "hello";
    printf("len = %d\n", strtlen1(p));

    return 0;
}

