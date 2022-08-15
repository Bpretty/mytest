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

	~S()
	{
		cout<< "析构函数"<<endl;
	}
	
private:
	int _count;
};


S t1()
{
	S s1;
	return s1;
}

int main()
{
	//S s1;
	//S s2= s1;
	
	S s1= t1();

	return 0;
}
