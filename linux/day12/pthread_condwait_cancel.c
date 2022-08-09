#include <func.h>

#define N 2

typedef struct{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}threadInfo_t;

void cleanupFunc( void* p )
{
    threadInfo_t *a = (threadInfo_t*)p;
    
    pthread_mutex_unlock(&a->mutex);

    printf("cancel succ\n");

}

void * threadFunc( void* p )
{
    threadInfo_t *a = (threadInfo_t*)p;
    pthread_mutex_lock(&a->mutex);
    pthread_cleanup_push(cleanupFunc, a);
    pthread_cond_wait(&a->cond, &a->mutex);
    //pthread_mutex_unlock(&a->mutex);
    pthread_cleanup_pop(1);

    pthread_exit(NULL);
}

int main()
{
    pthread_t thid[N];
    threadInfo_t data;
    pthread_mutex_init( &data.mutex, NULL );
    pthread_cond_init( &data.cond, NULL );

    int i, ret;
    for (i = 0; i < N; i++)
    {
        if ( 0!=pthread_create( thid+i, NULL, threadFunc, &data ) ){
            printf("fail create\n");
            return -1;
        }
    }

    usleep(1000);//保证子线程创建

    for (i=0; i<N; i++)
    {
        ret = pthread_cancel( thid[i] );
        if (-1== ret){
            printf("cancel fail\n");
            return -1;
        }
    }

    long longRet;
    for(i=0; i<N; i++)
    {
        ret = pthread_join( thid[i], (void**)&longRet );
        if (-1== ret){
            printf("join fail\n");
            return -1;
        }
    }

}
