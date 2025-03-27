#include "threadpool.h"


ThreadPool::ThreadPool(int n)
:m_Mtx()
,m_Cnd()
,m_bStop(false)
{
	while (n--)
	{
		m_Threads.emplace_back([this](){
			while (!m_bStop)
			{
				Node node;

				{
				std::unique_lock<mutex> locker(m_Mtx);
				m_Cnd.wait(locker, [this](){
					return !m_Que.empty() || m_bStop;
				});

				if (m_bStop)
				{
					cout << "exit..." << endl;
					return;
				}

				node = *m_Que.begin();
				m_Que.pop_front();
				}

				(*node.m_Func)(); 
			}

		});
	}

	cout << "创建线程完毕.." << endl;
}

ThreadPool::~ThreadPool()
{
	cout << "join线程中..." << endl;

	m_bStop = true;
	m_Cnd.notify_all();

	for (auto& t : m_Threads)
	{
		t.join();
	}
	cout << "join线程，end..." << endl;
}

