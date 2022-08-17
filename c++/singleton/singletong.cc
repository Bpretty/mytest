#include <iostream>
using namespace std;
// 单例模式，无自动释放

class Singleton
{
public:
    static Singleton* GetInstanse()
    {
        if (_p == nullptr)
        {
            _p = new Singleton();
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

//Singleton* Singleton::_p = Singleton::GetInstanse(); // 饱汉模式
Singleton* Singleton::_p = nullptr;                 //饿汉模式，多线程环境不安全

int main()
{
    Singleton* p = Singleton::GetInstanse();
    p->DestroyInstance();

    return 0;
}

