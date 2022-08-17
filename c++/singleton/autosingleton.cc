#include <iostream>
using namespace std;

//方案一： 使用嵌套类autorelease类+静态对象自动释放
// 饱汉模式
class Singleton
{
private:
    class AutoRelease
    {
    public:
        AutoRelease()
        {
            cout<< "AutoRelease()"<<endl;
            if (_p == nullptr)  _p = GetInstanse();
        }

        ~AutoRelease()
        {
            if (_p == nullptr) return;
            // 这里能访问到 _p因为其为静态成员，非静态要使用 this-> 访问
            delete _p;
            cout<< "~AutoRelease()"<<endl;
        }
    };

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
    static AutoRelease _auto;
};

Singleton* Singleton::_p = Singleton::GetInstanse();
Singleton::AutoRelease Singleton::_auto;

int main()
{
    Singleton* p = Singleton::GetInstanse();

    return 0;
}

