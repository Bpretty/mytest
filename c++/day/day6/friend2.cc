#include <iostream>

using namespace std;

class A
{
public:
	A(int x = 0)
	:_a(x)
	{}

	friend void test1( const A& a);
private:
	int _a;
};


void test1( const A& a)
{
	cout << a._a<<endl;

}

int main()
{
	A a;
	test1(a);
	
	return 0;
}
