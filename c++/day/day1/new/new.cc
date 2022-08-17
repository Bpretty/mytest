#include <iostream>

using namespace std;

void t1()
{
	
}

void t2()
{
	int *x = new int();
	cout << "x=" << *x <<endl;
	delete x;

	int *a = new int(2);
	cout << "a=" << *a <<endl;
	delete a;

	int *b = new int[10]();
	cout << "b=" << b[1] <<endl;
	delete [] b;

	int *c = new int[10];
	cout << "c=" << c[1]<<endl;
	delete [] c;
}

int main()
{

	t2();

	return 0;
}
