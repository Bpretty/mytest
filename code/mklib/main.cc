#include <iostream>
#include "f.h"
using namespace std;

int main()
{
    int a = 1, b = 2;
    int sum = add(1, 2);
    int s = sub(1, 2);
    cout <<"和为:" << sum << endl;
    cout <<"差为:" << s << endl;

    return 0;
}

