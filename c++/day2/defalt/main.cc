#include <iostream>

using namespace std;

int f(int a, int b=1, int c=2)
{
	return a+b+c;
}

int main()
{
	cout<<f(1,2)<<endl;

	return 0;
}
