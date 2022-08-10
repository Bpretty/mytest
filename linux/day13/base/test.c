#include <func.h>

int main()
{
    short a = 1;

    printf("a占用空间%ld, atoi占有空间 %ld\n", sizeof(a), sizeof( atoi("1")));
}
