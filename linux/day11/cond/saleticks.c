#include <func.h>

#define N 10000000

typedef struct{
    int ticks;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}threadInfo_t;

void * threadFunc1( void* p )
{
    threadInfo_t *pData = (threadInfo_t*)p;

    while(1)
    {
        pthread_mutex_lock( &pData->mutex );
        if (pData->ticks > 0){
            printf("1号，sale window, cur ticks: %d\n", pData->ticks);
            pData->ticks --;
            printf("1号，sale window, remain ticks: %d\n", pData->ticks);

            pthread_mutex_unlock( &pData->mutex );
            usleep(1000);
        }else{
            printf("1号， not ticks\n");
            
            pthread_cond_signal( &pData->cond );
            pthread_mutex_unlock( &pData->mutex );
            usleep(1000);
        }

    }

    pthread_exit( NULL );
}

void * threadFunc2( void* p )
{
    threadInfo_t *pData = (threadInfo_t*)p;

    while(1)
    {
        pthread_mutex_lock( &pData->mutex );
        if (pData->ticks > 0){
            printf("2号，sale window, cur ticks: %d\n", pData->ticks);
            pData->ticks --;
            printf("2号，sale window, remain ticks: %d\n", pData->ticks);

            pthread_mutex_unlock( &pData->mutex );
            usleep(1000);
        }else{
            printf("2号， not ticks\n");
            
            pthread_cond_signal( &pData->cond );

            pthread_mutex_unlock( &pData->mutex );
            usleep(1000);
        }
    }

    pthread_exit( NULL );
}

void * threadFunc3( void* p )
{
    threadInfo_t *pData = (threadInfo_t*)p;

    while(1)
    {
        pthread_mutex_lock( &pData->mutex );
        if (pData->ticks > 0){
            pthread_cond_wait( &pData->cond, &pData->mutex );
        }
        printf("3号， before add ：%d\n", pData->ticks);
        pData->ticks = 100;
        printf("3号，add ticks ：%d\n", pData->ticks);
        pthread_mutex_unlock( &pData->mutex );
    }

    pthread_exit( NULL );
}


int main()
{
    threadInfo_t data;
    bzero( &data, sizeof(data) );
    data.ticks = 100;
    pthread_mutex_init( &data.mutex, NULL );
    pthread_cond_init( &data.cond, NULL );

    pthread_t thid1;
    if ( 0!= pthread_create( &thid1, NULL, threadFunc1, &data ) ){
        printf("线程创建失败\n");
        return  -1;
    }
    pthread_t thid2;
    if ( 0!= pthread_create( &thid2, NULL, threadFunc2, &data ) ){
        printf("线程创建失败\n");
        return  -1;
    }
    pthread_t thid3;
    if ( 0!= pthread_create( &thid3, NULL, threadFunc3, &data ) ){
        printf("线程创建失败\n");
        return  -1;
    }

    usleep(1000);   

    pthread_join( thid1, NULL );
    pthread_join( thid2, NULL );
    pthread_join( thid3, NULL );

    return 0;
}
