#include <iostream>
#include <functional>
using namespace std;
using namespace std::placeholders;

class Demo
{
public:
    void print(int a, int b)
    {
        cout<< "Demo : " <<endl
            << a <<endl
            << b <<endl;
    }
};

int func(int a, int b, int c)
{
    cout<< "(a = " << a 
        << ",b = " << b
        << ",c = " << c
        <<endl;

    return a;
}

void t0()
{

    int x = 1;
    function<int(int)> f =  bind(func, _1, 2, 3);
    // 注意这里使用auto才可以传递多个参数, 当前只能传递一个参数
    f(1);

    auto f1 =  bind(func, _1, 2, 3);
    // 注意这里使用auto才可以传递多个参数
    f1(100,2,3);
}

void t1()
{
    Demo d;

#if 0
    function<void(int)> f = bind(&Demo::print, d, _1, 2  );
    f(3);

    function<void(int, int)> f1 = bind(&Demo::print, d, _2, _1 );
    f1(20, 30);
#endif
}

int main()
{
    t0();
    //t1();

    return 0;
}

