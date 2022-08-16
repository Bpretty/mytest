#include <iostream>

using namespace std;

class Demo
{
public:
	Demo(int x = 0)
	:_n(x)
	{}

	friend ostream& operator<<( ostream& os,  const Demo& t );
private:
	int _n;
};

ostream& operator<<(ostream& os, const Demo& t)
{
	os<< t._n <<endl;
}

int main()
{
	Demo d(1);
	cout<< d;

	return 0;
}
