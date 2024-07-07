#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    printf("共有%d个参数\n", argc);
    for(int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    return 0;
}

