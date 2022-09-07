#include <iostream>
#include <queue>
using namespace std;

// 优先级队列使用，重载了函数运算符

class Data
{
public:
    Data(int a=1, int b=2)
    :_a(a)
    ,_b(b)
    {
    }

    friend bool operator<(const Data& a, const Data& b);
    friend ostream& operator<<( ostream& os, const Data& a);
private:
    int _a;
    int _b;
};

ostream& operator<<( ostream& os, const Data& a)
{
    os<< "a = " << a._a << ", b = " << a._b <<endl;
    return os;
}

 bool operator<(const Data& a, const Data& b)
{
    if ( a._a != b._b ) return a._a < b._a;

    return a._a < b._b;
}

void test0()
{
    priority_queue<Data> queue;
    queue.push( Data(0,0) );
    queue.push( Data(0,1) );

    while(!queue.empty())
    {
        cout<<queue.top()<<endl;
        queue.pop();
    }

}

int main()
{
    test0();

    return 0;
}

