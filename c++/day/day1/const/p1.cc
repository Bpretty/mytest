#include <iostream>
using namespace std;

void t1()
{
	int a = 1;
	int b = 2;

	// 常量指针：可以改地址，不能改值
	const int * p1 = &a;
	//*p1 = -1;	//erro
	cout << *p1<<endl;

	p1 = &b;
	cout<< *p1<<endl;

	// 指针常量：不可以改地址，可以改值
	int * const p2 = &a;
	//p2 = &b;	//erro
	*p2 = -2;
	cout<<*p2<<endl;
}

int main()
{
	t1();

	return 0;
}
