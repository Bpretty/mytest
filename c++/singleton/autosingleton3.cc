#include<func.h>
#include <iostream>
using namespace std;

//方案三： 使用 atexit
class Singleton
{
public:
    static Singleton* GetInstanse()
    {
        pthread_once( &_once, init );

        return _p;
    }

    static void init()
    {
        if (_p == nullptr)
        {
            _p = new Singleton();
            atexit(DestroyInstance);
        }
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
    static pthread_once_t _once;
};

Singleton* Singleton::_p = Singleton::GetInstanse();    //饱汉模式
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

int main()
{
    Singleton* p = Singleton::GetInstanse();

    return 0;
}

