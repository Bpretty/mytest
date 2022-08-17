#include <iostream>

using namespace std;

class A;

class B
{
public:
	void func( const A& a);
private:
	//int _b;
};

void B::func( const A& a)
{
	cout<< a._a<<endl;
}

class A
{
public:
	A(int x)
	:_a(x)
	{}

	friend void B::func( const A& a);
private:
	int _a;
};



void test1()
{
	A a1(1);
	B b1;	// 使用 B b1(); 时编译器认为是函数声明，故之前错误

	b1.func(a1);
}

int main()
{
	test1();
	
	return 0;
}
