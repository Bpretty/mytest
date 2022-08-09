#include <func.h>

void* func(void * p)
{
    sleep(1);

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
