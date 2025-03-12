#include "common.h"

class SingletonMutex
{
private:
	SingletonMutex(){};
	~SingletonMutex(){};
public:
	static SingletonMutex* Get()
	{
		if (_p == nullptr)
		{
			cout << "111" << endl;
			std::lock_guard<std::mutex> lock(_mutex);
			if (_p == nullptr)
			{
				_p = new SingletonMutex();
				cout << "第一次创建对象" << endl;
			}
		}

		return _p;
	}

	static void destroy()
	{
		if (_p == nullptr)
		{
			delete _p;
			_p = nullptr;
		}
	}

private:
	static SingletonMutex* _p;
	static mutex _mutex;
};

SingletonMutex* SingletonMutex::_p = nullptr;
mutex SingletonMutex::_mutex;


int main()
{
	SingletonMutex* p1 = SingletonMutex::Get();
	SingletonMutex* p2 = SingletonMutex::Get();
	SingletonMutex* p3 = SingletonMutex::Get();

	p1->destroy();

	return 0;
}
