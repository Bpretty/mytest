#include <func.h>

void cleanFunc( void * p )
{
    printf("i am clean func\n");
}

void* func(void * p)
{
    pthread_cleanup_push( cleanFunc, NULL )
    printf("this is child thread \n");

    pthread_exit(NULL);

    pthread_cleanup_pop(0);// 放到最后没关系，只是不会执行
}

int main()
{
    pthread_t threadid; 
    int ret = pthread_create( &threadid, NULL, func, NULL);
    if (0!=ret){
        printf("erro: %s\n", strerror(ret));
        return -1;
    }

    //pthread_cancel(threadid);

    long thRet;
    pthread_join(threadid, (void**)&thRet);
    printf("子线程返回值为：%ld\n", thRet);

    return 0;
}
