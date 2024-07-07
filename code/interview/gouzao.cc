#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

void f()
{
    cout<< "f()"<<endl;
}

void f(char* p)
{
    cout<< "f(char*)" <<endl;
}

class Demo
{
public:
    Demo()
    {
        cout<< "Demo()" <<endl;
    }

    Demo(char* ch)
    {
        if (ch != nullptr)
        {
            _str = new char[strlen(ch)+1]();
        }else{
            _str = new char[1]();
        }

        cout<< "Demo(char*)"<<endl;
    }
private:
    char* _str;
};

int main()
{
    f(nullptr);

    Demo(nullptr);

    return 0;
}

