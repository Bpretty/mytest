#include <iostream>

using namespace std;

// 在同一个文件可以分为声明和实现，不同文件则不行

inline int add(int a, int b);

int main()
{
	cout<< add(1, 2)<<endl;

	return 0;
}


int add(int a, int b)
{
	return a+b;
}
