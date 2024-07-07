#include <stdio.h>

#define OPEN_CPP 0

#if OPEN_CPP
#include <iostream>
using namespace std;
#endif

void t0()
{
    printf("%ld\n", sizeof(int));
}

void t1()
{
    int a = 1;
    printf("%ld\n", sizeof(a++));

    printf("增长后%d\n", a );
}

struct Test
{
    char a;
    double b;
    int c;
    char d;
};

struct Test1
{
    char a[3];
    int b;
};

void t2()
{
#if OPEN_CPP
    cout<< sizeof(long)<<endl;
    cout<< sizeof(long long)<<endl;
    cout<<sizeof(Test)<<endl;

    cout<<sizeof(Test1)<<endl;
#endif

    printf("%ld\n", sizeof(struct Test));
}

void t3()
{
    int a[] = {1,2,3};

    int (&b)[3] = a;
    int (*c)[3] = &a;
    
    printf("%ld, %d\n", sizeof(c), c[0][1]);
    printf("%ld\n", sizeof(b));
}

int main()
{
    //t0();
    //t1();
    //t2();
    t3();

    return 0;
}

