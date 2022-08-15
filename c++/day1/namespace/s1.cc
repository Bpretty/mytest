#include <iostream>

namespace ly
{
	int a=1;

	int get()
	{
		return -1;
	}
}

void t( int x )
{
	std::cout<<x<<std::endl;
}

int a = 2;

int main()
{
	int a = 3;

	t(a);
	t(::a);
	t(ly::a);

	t( ly::get() );

	return 0;
}
