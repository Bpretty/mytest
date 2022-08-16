#include <iostream>

using namespace std;

class A
{
public:
	void print()
	{
		cout<< "i am print"<<endl;
	}
};

class B
:private A
{
public:
	void t()
	{
		print();
	}
};

int main()
{
	B b1;
	//b1.print();
	b1.t();

	return 0;
}
