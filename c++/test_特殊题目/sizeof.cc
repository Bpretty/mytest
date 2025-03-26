#include "common.h"

class A
{
	virtual void foo(){}
};

class B : A
{
	virtual void foo() { }

	void bar() {}
};

int main()
{
	cout << sizeof(A) << "," <<  sizeof(B) << endl;
	return 0;
}

