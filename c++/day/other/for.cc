#include <vector>
#include <iostream>
using namespace std;

void t()
{
    vector<int> v{1,2,3,4,5};

    for(int& n: v)
    {
        n = n*2;
        cout<< n <<endl;
    }

    for(int& n: v)
    {
        cout<< n <<endl;
    }
}

int main()
{
    t();
    return 0;
}

