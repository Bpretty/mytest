#include <iostream>
#include <iostream>
using namespace std;

class Test
{
public:
    Test(int a = 0)
    :_a(a)//只有在这里才是初始化
    {
        
        // 在这里不是初始化，而是赋值了
        //_a = a;
        
        print();
    }
private:
    void print()
    {
        cout<< _a << endl;
    }

private:
    const int _a ;
};

int main()
{
    Test t;
    return 0;
}

