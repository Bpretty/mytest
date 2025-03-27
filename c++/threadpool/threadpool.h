#include "common.h"

#ifndef __POOL__
#define __POOL__

struct Node
{
	std::function<void(int)> m_Func;
	int m_Arg;
};

class ThreadPool
{
public:
	ThreadPool(int n = 5);
	~ThreadPool();

	int PushQueue(Node& node);
	Node PopQueue();

public:
	bool m_bStop;
private:
	vector<thread> m_Threads;
	std::list<Node> m_Que;
	std::mutex m_Mtx;
	std::condition_variable m_Cnd;
};

#endif
