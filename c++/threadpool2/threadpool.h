#include "common.h"

#ifndef __POOL__
#define __POOL__

struct Node
{
	//std::function<void()> m_Func;
	std::shared_ptr<std::packaged_task<void()>> m_Func;
};

class ThreadPool
{
public:
	ThreadPool(int n = 5);
	~ThreadPool();

	Node PopQueue();

	template <typename Fn, typename... Args >
	auto PushQueue(Fn&& f, Args&&... args) -> std::future<decltype(f(args...))>
	{
		using return_type = decltype(f(args...));

		auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<Fn>(f), std::forward<Args>(args)...)
        );
        	std::future<return_type> res = task->get_future();

		Node node = {task};
		{
			std::lock_guard<mutex> locker(m_Mtx);
			m_Que.push_back(std::move(node));
		}

		m_Cnd.notify_one();

		return res;
	}
public:
	bool m_bStop;
private:
	vector<thread> m_Threads;
	std::list<Node> m_Que;
	std::mutex m_Mtx;
	std::condition_variable m_Cnd;
};

#endif
