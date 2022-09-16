#include <iostream>
using namespace std;

void t()
{
    int a[3][3] = { 1,2,3,4,5,6,7,8,9};
    
    cout<< a <<endl;
    cout<< a[0] <<endl;
    cout<< &a[0][0] <<endl;

    cout<< "-----" <<endl;

    int* p1 = &a[2][1];
    cout<< *p1<<endl;

    int *p2 = a[2];
    cout<< p2 <<endl;
    cout<< &a[2][0]<<endl;

    cout<< "-----" <<endl;
    int* p4 = *(a+2)+1;
    cout<< *p4 <<endl;
    cout<< p4 <<endl;
    cout<< p1<<endl;

}

int main()
{
    t();

    return 0;
}

