#include "common.h"

int func(int a, int b)
{
	cout << "int func(int, int)" << endl;
	return a + b;
}

void t()
{
	std::packaged_task<int()> task(std::bind(func, 1, 1));
	std::future<int> result = task.get_future();

	task();
	cout << "task的结果是:" << result.get() << endl;
}

void t2()
{
	std::packaged_task<void(int)> task([](int a)
	{
		cout << a * 10 << endl;
	});
	std::future<void> result = task.get_future();
	
	task(1);
	//cout << "task的结果是:" << result.get() << endl;
}

void t3()
{
	std::packaged_task<void(int)> task([](int a)
	{
		cout << a * 10 << endl;
	});

	// 因为 packaged_task 重载了 operator() ，所以可以作为线程构造函数参数
	thread t1(std::move(task), 2);
	t1.join();
}

int main()
{
	t3();

	return 0;
}
