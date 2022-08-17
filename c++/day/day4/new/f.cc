#include <iostream>

using namespace std;

class S
{
public:
	S(int a = 0)
	:_count(a)
	{
		cout<<"构造函数"<<endl;
	}

	int get()
	{
		return _count;
	}
	void set(int a)
	{
		_count = a;
	}

	S(const S& S1)
	{
		cout<<"复制构造函数"<<endl;
	}

	const S& operator=(const S& s1)
	{
		cout<< "赋值函数"<<endl;

		if (this == &s1) return *this;

		this->_count = s1._count;

		return *this;
	}
	
	static
	void* operator new(size_t n)
	{
		cout<< "operator new"<<endl;

		return malloc( n );
	}

	static
	void operator delete( void* p )
	{
		cout<< "operator delete"<<endl;
		if (p==nullptr)	return;

		free(p);
	}

	~S()
	{
		cout<< "析构函数"<<endl;
	}
	
private:
	int _count;
};


void t1()
{
	S s1(1);
	S s2(2);
	//s1 = s2;
	s1.operator=(s2);	// 和注释的等价
	cout<<s1.get()<<endl;
}

void t2()
{
	S *p = new S();
	cout << p->get() <<endl;

	delete p;
}

int main()
{
	//t1();

	t2();

	return 0;
}
