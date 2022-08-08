#include <func.h>

// 栈空间虽然私有，但是进程地址对其中的每个线程权限一样，所以可以访问

void* func(void * p)
{
    printf("i am child thread\n");
    printf("arg : %d\n", *(int*)p );
    *(int*)p = 5;
}

int main()
{   
    int a = 10;

    pthread_t threadid; 
    int ret = pthread_create( &threadid, NULL, func, &a);
    if (0!=ret){
        printf("erro: %s\n", strerror(ret));
        return -1;
    }

    printf("i am main thread\n");

    pthread_join(threadid, NULL);
    
    printf(" a = %d\n", a);

    return 0;
}
