#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

#include <unistd.h>
using namespace std;

std::mutex m_MyMutext;
int m_Value = 0;

void print(int id)
{
    while(1)
    {
        {
            lock_guard<std::mutex> myMutex(m_MyMutext);
            if(m_Value >= 100000)
            {
                cout<<"到达终点:"<<m_Value<<endl;;
                break;
            }
            m_Value++;
            cout<<"thread: "<<id<<"-->"<<m_Value<<endl;;
        }
    }
}

#if 0 //测试mutex锁
int main()
{
    std::thread t1(print , 1);
    std::thread t2(print , 2);

    t1.join();
    t2.join();

    return 0;
}
#endif

int main()
{
    return 0;
}
