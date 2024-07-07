#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void t0()
{
    FILE* fp = fopen("file.txt", "w+");
    if(fp == NULL)
    {
        perror("fopen");

        return;
    }

    fprintf(fp, "test%d : value %s", 10, "hh");
    fclose(fp);
}

void t1()
{
    FILE* fp = fopen("file.txt", "r+");
    if(fp == NULL)
    {
        perror("fopen");

        return;
    }

    int value = 0;
    char str[100] = {0};
    //int ret = fscanf(fp, "test%d : value %s", &value, str);
    int ret = fscanf(fp, "%s", str);
    //if (ret <= 0)
    //{
        perror("fscanf");
    //    return;
    //}

    printf("获取的数据是：%d  %s\n", value, str);
    
    fclose(fp);
}

int main()
{
    //t0();
    t1();

    return 0;
}

