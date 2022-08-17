#include <iostream>
using namespace std;

class Demo
{
public:
    Demo(int x = 0)
    :_a( x )
    ,_b( 2 )
    {
        //-a = 1; // car!! 在这里赋值不是初始化
        
        print();
    }

    void print()
    {
        cout<< _a <<endl;
    }
private:
    const int _a;
    const int& _b;
};

void t()
{
    Demo d;
}


int main()
{
    t();

    return 0;
}

