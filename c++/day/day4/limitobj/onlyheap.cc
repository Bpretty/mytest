#include <iostream>

using namespace std;

// 只能在堆上生成对象
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

	void destroy()
	{
		delete this;
	}
private:
	~S()
	{
		cout<< "析构函数"<<endl;
	}
	
private:
	int _count;
};


int main()
{
	S *p = new S();
	cout<< p->get()<<endl;
	p->destroy();

	//S s1; 	//erro

	return 0;
}
