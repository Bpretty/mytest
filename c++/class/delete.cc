#include <func.h>
#include <iostream>
using namespace std;


int main()
{
    char* p = new char[6]();
    strcpy( p, "hello");

    cout<< p << endl;

    char* p1 = p+1;
    delete p;
    cout<< *p1 <<endl;

    return 0;
}

