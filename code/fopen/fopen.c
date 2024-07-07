#include <stdio.h>

void t1()
{
    FILE* fp = fopen("t.txt", "rb");
    if (NULL != fp)
    {
        printf("open succ\n");
    }else{
        printf("open fail\n");
    }

    fclose(fp);
    fp = NULL;
}

int main()
{
    t1();

    return 0;
}

