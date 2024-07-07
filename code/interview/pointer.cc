#include <iostream>
using namespace std;

void t()
{
    int x = 1;

    const int * p1 = &x;
    p1++;
    //(*p1)++; //erro
    
    const int* const p2 = &x;
    //p2++; //erro
}

//void f1(int a[2][3])  //可以
//void f1(int a[][3])  //可以
void f1(int(*a)[3])
//void f1(int a[][])  //erro
{
    for(int i = 0; i < 2; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            cout<< "i = "<<i
                <<",j = "<<j
                <<"  "
                << a[i][j] <<endl;
        }
    }
}

void t1()
{
    int a[2][3] = {
        {1,2},
        {10,20,30}
    };

#if 0
    f1(a);
#endif

    printf("%p\n", a);
    printf("%p\n", &(a[0][0]));
}

int main()
{
    t1();
    return 0;
}

