#include <iostream>
using namespace std;

void print(int a)
{
    //多次调用此函数 b 的值仍然为第一次赋的值
    static int b = a;
    cout<<"var == "<< b <<endl;
}

static int x = 1;

int main()
{
    print(1);
    print(2);

    cout<< "x == " << x <<endl;
    x = 2;
    cout<< "x == " << x <<endl;
    return 0;
}

