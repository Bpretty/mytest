#include <iostream>
using namespace std;

class Test
{
public:
    Test(int a = 1)
    :_a(a)
    {}

    void print() const
    {
        cout<< "begin: -a = " << _a <<endl;

        Test *const p = const_cast<Test *const>(this);

        p->_a = 2;

        cout<< "aften: -a = " << _a <<endl;

        //_a = 3; //erro
    }


private:
    int _a;
};

int main()
{
    Test t;
    t.print();

    return 0;
}

