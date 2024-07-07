#include <iostream>
using namespace std;



int main()
{
    int* p[10] = {0};

    for(int i = 0; i < 10; i++)
    {
        p[i] = &i;
    }

    for(int j = 0; j<10; j++)
    {
        cout<< p[j] <<endl;
        cout<< *(p[j]) <<endl;
    }

    return 0;
}

