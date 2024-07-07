#include <stdio.h>
#include <stdlib.h>

int main()
{
    const char* env = "CFLAGS";
    char* val = getenv(env);

    printf("%s\n", val);
    return 0;
}

