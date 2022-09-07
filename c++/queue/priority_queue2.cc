#include <iostream>
#include <queue>
using namespace std;

// 优先级队列使用，使用了函数对象

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
    friend class Less;
private:
    int _a;
    int _b;
};

ostream& operator<<( ostream& os, const Data& a)
{
    os<< "a = " << a._a << ", b = " << a._b <<endl;
    return os;
}

#if 0
 bool operator<(const Data& a, const Data& b)
{
    if ( a._a != b._b ) return a._a < b._a;

    return a._a < b._b;
}
#endif

struct Less
{
    bool operator()(const Data& a, const Data& b)
    {
        if ( a._a != b._b ) return a._a < b._a;

        return a._a < b._b;

    }
};

void test0()
{
    priority_queue<Data, vector<Data>, Less> queue;
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

