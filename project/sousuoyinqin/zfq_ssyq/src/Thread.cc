 ///
 /// @file    Thread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-04 09:51:40
 ///
 

#include "../include/Thread.h"
#include "../include/redis.h"
#include <iostream>
using std::cout;
using std::endl;

__thread Redis* predis;

namespace wd
{

Thread::Thread(ThreadCallback && cb)
: _pthid(0)
, _cb(std::move(cb))
, _isRunning(false)
{
	cout << "Thread()" << endl;
}

void Thread::start()
{
	pthread_create(&_pthid, NULL, threadFunc, this);	
	_isRunning = true;
}

void * Thread::threadFunc(void * arg)
{
    predis = new Redis();
    predis->connect("127.0.0.1", 6379);
	Thread * pthread = static_cast<Thread*>(arg);
	if(pthread)
		pthread->_cb();
    delete predis;
	return nullptr;
}

void Thread::join()
{
	if(_isRunning)
		pthread_join(_pthid, NULL);
}

Thread::~Thread()
{
	if(_isRunning) {
		pthread_detach(_pthid);	
	}
	cout << "~Thread()" << endl;
}

}//end of namespace wd
