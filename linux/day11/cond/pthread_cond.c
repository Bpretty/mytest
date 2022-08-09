#include <func.h>

#define N 10000000

typedef struct{
    int sum;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}threadInfo_t;

void * threadFunc( void* p )
{
    threadInfo_t *pData = (threadInfo_t*)p;
    pthread_mutex_lock( &pData->mutex );
    pthread_cond_wait( &pData->cond, &pData->mutex );
    pthread_mutex_unlock( &pData->mutex );

    printf( "i am child thread\n " );

    pthread_exit( NULL );
}

int main()
{
    threadInfo_t data;
    bzero( &data, sizeof(data) );
    pthread_mutex_init( &data.mutex, NULL );
    pthread_cond_init( &data.cond, NULL );

    pthread_t threadid;
    if ( 0!= pthread_create( &threadid, NULL, threadFunc, &data ) ){
        printf("线程创建失败\n");
        return  -1;
    }
    sleep(1);   // 睡觉是为了等待子线程创建，确保子线程能收到信号
    pthread_cond_signal( &data.cond );
    pthread_join( threadid, NULL );

    return 0;
}
