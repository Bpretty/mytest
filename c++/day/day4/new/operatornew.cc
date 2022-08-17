#include <iostream>

using namespace std;

// 放在类之外则是针对所有的类型起作用
// 放在类内部也可以使用静态类型定义

void* operator new(size_t n)
{
	cout<< "operator new"<<endl;

	return malloc( n );
}

void operator delete( void* p )
{
	cout<< "operator delete"<<endl;
	if (p==nullptr)	return;

	free(p);

}

int main()
{
	int *p = new int(0);
	delete p;

	return 0;
}
