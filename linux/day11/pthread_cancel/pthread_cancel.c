#include <func.h>

// 有时候打印出两个 “i am child thread”，猜测和线程关闭输出有关

void* func(void * p)
{
    printf("i am child thread\n");
    sleep(1);
    printf("after sleep\n");

    return NULL;
}

int main()
{
    pthread_t threadid; 
    int ret = pthread_create( &threadid, NULL, func, NULL);
    if (0!=ret){
        printf("erro: %s\n", strerror(ret));
        return -1;
    }

    pthread_cancel(threadid);

    long thRet;
    pthread_join(threadid, (void**)&thRet);
    printf("子线程返回值为：%ld\n", thRet);

    return 0;
}
