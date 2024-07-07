#include <iostream>
using namespace std;

// 均为1
void test()
{
    char * p1 = "a";
    char * p2 = "a";

    const char * const cp1 = "a";
    const char * cp2 = "a";


    cout<< (p1==p2)<<endl;
    cout<< (cp1==cp2)<<endl;
    cout<< (p1==cp2)<<endl;
    cout<< (cp1==p2)<<endl;
}

int main()
{
    test();

    return 0;
}

