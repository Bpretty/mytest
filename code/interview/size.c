#include <stdio.h>
#include <string.h>

#pragma pack(1)
struct pt{
    char a;
    int b;
    int c;
};
#pragma pack()

#pragma pack(8)
struct pt1
{
    short a;
    int b;
};
#pragma pack()

#pragma pack(8)
struct pt2
{
    short a;
    short b;
    char c;

};
#pragma pack()

void t()
{
    size_t len = sizeof(struct pt);
    printf("%ld\n", len);
}

void t1()
{
    size_t len = sizeof(struct pt1);
    printf("%ld\n", len);
}

void t2()
{
    size_t len = sizeof(struct pt2);
    printf("%ld\n", len);
}

void t3()
{
    char* p = NULL;

    //printf("对空指针使用strlen的值：%ld\n", strlen(p));
}

int main()
{
    //t();
    //t1();
    //t2();
    t3();

    return 0;
}

