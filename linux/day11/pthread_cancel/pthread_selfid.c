#include <func.h>


void* func(void * p)
{
    printf("i am child thread\n");
}

int main()
{
    pthread_t threadid; 
    int ret = pthread_create( &threadid, NULL, func, NULL);
    if (0!=ret){
        printf("erro: %s\n", strerror(ret));
        return -1;
    }

    printf("i am main thread, threadid = %ld\n", pthread_self());

    pthread_join(threadid, NULL);

    return 0;
}
