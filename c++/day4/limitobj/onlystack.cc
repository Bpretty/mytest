#include <iostream>

using namespace std;

// 只能在栈上生成对象，不能在堆上生成对象
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

	~S()
	{
		cout<< "析构函数"<<endl;
	}

private:
	// 不需要用到了，故仅提供声明即可
	static void* operator new(size_t n);
	static void operator delete( void* p );
		
private:
	int _count;
};


int main()
{
	//S *p = new S();	// erro
	//cout<< p->get()<<endl;
	//p->destroy();

	S s1;
	cout<< s1.get()<<endl;

	return 0;
}
