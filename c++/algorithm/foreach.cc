#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void print(int& i)
{
    //++i;
    cout<< i<<endl;
}

int main()
{
    vector<int>  vec{1,2,3};

    // 算法库中定义为了非修改式序列，其实可以修改
    // 传递一元函数即可
    for_each(vec.begin(), vec.end(), print);

    return 0;
}

