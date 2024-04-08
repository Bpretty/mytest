#include <math.h>
#include <iostream>
using namespace std;

// 因为精确度的原因不能使用==判断两个double类型值
void test()
{
    double a1 = 1.23;
    double a2 = 1.2300000;

    if (a1 == a2)
    {
        cout<< "值相等"<<endl;
    }else{
        cout<< "不等于"<<endl;
    }
}

void test2()
{
    double a1 = 1.23;
    double a2 = 1.2300000;
    bool flag = fabs(a1-a2) < 1e-7;
    if (flag)
        cout<< "equal"<<endl;
    else
        cout<< "equal"<<endl;
}

int main()
{
    //test();
    test2();

    return 0;
}

