#include <func.h>

// 返回值是整数的情况

void* func( void * p )
{
    printf("i am child thread\n");
    return (void*)6;
}

int main()
{
    pthread_t threadid;
    int ret = pthread_create(&threadid, NULL, func, NULL );
    if (ret!=0){
        printf("线程创建失败\n");
        return -1;
    }

    long longRet ;
    pthread_join( threadid, (void**)&longRet );
    printf("返回值是：%ld\n", longRet );

    return 0;
}
