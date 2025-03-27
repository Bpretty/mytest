#include "threadpool.h"

void func(int n)
{
	cout << "Thread " << this_thread::get_id() << " : i am func() , n = " << n<< endl;
}

//int func2(int n, int n2)
void func2(int n, int n2)
{
	cout << "Thread " << this_thread::get_id() << " : i am func2() , n2 = " << n<< endl;
}

int main()
{
	ThreadPool pool;
	pool.PushQueue(func, 1);
	pool.PushQueue(func2, 10, 20);

#if 0
	for (int i = 0; i < 1000; i++)
	{
		Node node{func, i};
		pool.PushQueue(node);
	}
#endif

	sleep(3);
	pool.m_bStop = true;
	cout << "end main" << endl;

	return 0;
}
