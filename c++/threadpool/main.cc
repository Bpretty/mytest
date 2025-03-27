#include "threadpool.h"

void func(int n)
{
	cout << "Thread " << this_thread::get_id() << " : i am func() , n = " << n<< endl;
}

int main()
{
	ThreadPool pool;
	for (int i = 0; i < 1000; i++)
	{
		Node node{func, i};
		pool.PushQueue(node);
	}

	sleep(3);
	pool.m_bStop = true;
	cout << "end main" << endl;

	return 0;
}
