#include <iostream>
using namespace std;

// from effective c++

class Singleton
{
public:
    static Singleton& getInstance()
    {
        static Singleton instance;
        cout<< "getInstance()"<<endl;

        return instance;
    }
    
    void print()
    {
        cout<< "i am print function"<<endl;
    }

private:
    Singleton(){}
    ~Singleton(){}
    //Singleton(const Singleton& a){}
    Singleton& operator=(const Singleton& a){ return *this; }
};



class Test
{
public:
    Test()
    {
        cout<< "Test()"<<endl;
    }
        
    Test(const Test& t)
    {
        cout<< "Test(const Test&)"<<endl;
    }

    Test& operator=(const Test& t)
    {
        cout<< "operator=(const Test&)"<<endl;
        return *this;
    }
};

int main()
{
    Singleton::getInstance().print();

#if 0
    Test a;
    Test t = a;
    t = a;
#endif

    return 0;
}

