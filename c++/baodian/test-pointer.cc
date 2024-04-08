#include <stdio.h>
#include <iostream>

using namespace std;

void t1()
{
    int a = 1;
    int b = 2;

    int *s[2] = {&a, &b};
    int s1[2] = {a, b};

    int  (*p1)[2] = &s1; // 注意此处是 &s1，s1的类型是 int*
                        // p1为指向拥有两个元素int数组的指针
#if 0
    int* (*p2)[2] = &s;

    cout<< **p2[0]<<endl;
#endif

    cout<< (*p1)[0]<<endl;
    cout<< (*p1)[1]<<endl;

    cout<< p1[0][0]<<endl;
    cout<< p1[0][1]<<endl;
}

int main()
{
    t1();

    return 0;
}

