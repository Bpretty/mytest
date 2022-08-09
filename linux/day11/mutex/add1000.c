#include <func.h>

#define N 10000000

typedef struct{
    int sum;
    pthread_mutex_t mutex;
}threadInfo_t;

void * threadFunc( void* p )
{
    threadInfo_t *a = (threadInfo_t*)p;
    for( int i = 0; i < N; i++ )
    {
        pthread_mutex_lock(&a->mutex);
        a->sum+= 1;
        pthread_mutex_unlock(&a->mutex);
    }
}

int main()
{
    threadInfo_t data;
    bzero( &data, sizeof(data) );
    pthread_mutex_init( &data.mutex, NULL );

    pthread_t threadid;
    if ( 0!= pthread_create( &threadid, NULL, threadFunc, &data ) ){
        printf("线程创建失败\n");
        return  -1;
    }
    // main线程加值
    for( int i = 0; i < N; i++ )
    {
        pthread_mutex_lock(&data.mutex);
        data.sum+= 1;
        pthread_mutex_unlock(&data.mutex);
    }

    pthread_join( threadid, NULL );
    printf("累加和为：%d\n", data.sum);

    return 0;
}
