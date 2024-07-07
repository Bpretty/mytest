#include <iostream>
#include <vector>
using namespace std;

template <class T>
void display(const T& t)
{
    //typename T::iterator beg = t.begin();
    for(auto iter = t.begin(); iter != t.end(); iter++)
    {
        cout<< *iter <<endl;
    }
}

void t()
{
    for(int i = 0; i < 5; i++)
    {
        vector<int> vec;
        vec.push_back(i);

        cout<< vec.size()
            << ","
            << vec.capacity()
            <<endl;

        display(vec);
    }
}

int main()
{
    t();

    return 0;
}

