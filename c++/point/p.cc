#include <func.h>

#include <iostream>
using namespace std;

void t1()
{
    char* p1 = nullptr;
    int* p2 = nullptr;

    double i1 = 1;
    short s1 = 1;

    cout<< sizeof(p1)<<endl;
    cout<< sizeof(p2)<<endl;
    cout<< sizeof(i1)<<endl;
    cout<< sizeof(s1)<<endl;
}

void t2()
{
    //cout<< nullptr<<endl; //erro
    
    cout<< NULL <<endl;
}

int main()
{
    //t1();

    t2();

    return 0;
}

