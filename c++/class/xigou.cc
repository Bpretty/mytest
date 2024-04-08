#include <iostream>
using namespace std;

class A
{
public:
    A()
    {
        cout<<"A()"<<endl;
    }

    ~A()
    {
        cout<<"~A()"<<endl;
    }

};

int main()
{
    A* p = new A[10];

    delete[] p;

    return 0;
}

