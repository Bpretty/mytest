#include <func.h>


void* func(void * p)
{
    int *a = (int*)p;
    printf("i am child thread, %d\n", *a);

    return NULL;
}


int main()
{
    pthread_t threadid1, threadid2; 
    int sum1 = 1;
    int ret = pthread_create( &threadid1, NULL, func, &sum1 );
    if (0!=ret){
        printf("erro: %s\n", strerror(ret));
        return -1;
    }

    int sum2 = 2;   // 使用同一个sum存在并发问题
    ret = pthread_create( &threadid2, NULL, func, &sum2 );
    if (0!=ret){
        printf("erro: %s\n", strerror(ret));
        return -1;
    }


    printf("i am main thread\n");

    pthread_join(threadid1, NULL);
    pthread_join(threadid2, NULL);

    return 0;
}
