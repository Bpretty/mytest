#include <func.h>


void* func(void * p)
{
    printf("i am child thread\n");
    printf("arg : %s\n", (char*)p );
    free(p);
}

int main()
{   
    char* p = (char*)malloc(128);
    strcpy(p, "我是测试内存\n");
    pthread_t threadid; 
    int ret = pthread_create( &threadid, NULL, func, p);
    if (0!=ret){
        printf("erro: %s\n", strerror(ret));
        return -1;
    }

    printf("i am main thread\n");

    pthread_join(threadid, NULL);

    return 0;
}
