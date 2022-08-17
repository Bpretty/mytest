#include<func.h>
#include <iostream>
using namespace std;

//方案二： 使用 atexit
class Singleton
{
public:
    static Singleton* GetInstanse()
    {
        if (_p == nullptr)
        {
            _p = new Singleton();
            atexit(DestroyInstance);
        }

        return _p;
    }

    static void DestroyInstance()
    {
        if ( _p == nullptr ) return ;

        delete _p;
        _p = nullptr;
    }
private:
    Singleton(){ cout<< "Singleton()"<<endl;}
    ~Singleton(){ cout<< "~Singleton()"<<endl;}

private:
    static Singleton* _p;
};

Singleton* Singleton::_p = Singleton::GetInstanse();    //饱汉模式

int main()
{
    Singleton* p = Singleton::GetInstanse();

    return 0;
}

