#include <func.h>

#include <iostream>
using namespace std;

class String
{
public:
    String()
    :_pStr( new char[1]() )
    {
        cout << "String()"<<endl;
    }

    String( char* p )
    :_pStr( new char[strlen(p) + 1]())
    {
        strcpy( _pStr, p );

        cout << "String(char*)"<<endl;
    }

    String( const String& str)
    :_pStr( new char[strlen(str._pStr) + 1]() )
    {
        strcpy( _pStr, str._pStr );

        cout << "String(const String&)"<<endl;
    }

    const String& operator=( const String& str)
    {
        cout << "String operator="<<endl;

        if ( this == &str ) return *this;

        delete[] _pStr;
        _pStr = new char[strlen( str._pStr ) + 1]();
        strcpy( _pStr, str._pStr );
    }

    ~String()
    {
        cout << "~String()"<<endl;

        if ( _pStr != nullptr )
        {
            delete[] _pStr;
            _pStr = nullptr;
        }
    }

    friend ostream& operator<<( ostream& os, const String& str);
private:
    char* _pStr;
};

ostream& operator<<( ostream& os, const String& str)
{
    cout<< str._pStr <<endl;
}


void t1()
{
    String s1;
    String s2("hello");

    cout<<s2;
}

void t2()
{
    String s1("wo");
    cout<< s1 <<endl;

    String s2 = s1;
    cout<< s2 <<endl;

    String s3("hello");
    cout<< s3 <<endl;

    s1 = s3;
    cout<< s1 <<endl;
}

int main()
{
    t2();

    return 0;
}

