#include "common.h"

class SingletonMutex
{
private:
	// 注意只把构造设为了私有，析构并不是私有
	SingletonMutex(){};

public:

	static SingletonMutex& Get()
	{
		static SingletonMutex s;
		return s;
	}

	void print()
	{
		cout << "i am print()" << endl;
	}
};


int main()
{
	SingletonMutex p1 = SingletonMutex::Get();
	SingletonMutex p2 = SingletonMutex::Get();
	SingletonMutex p3 = SingletonMutex::Get();

	p1.print();
	p2.print();
	p3.print();

	return 0;
}
