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

    printf("i am main thread\n");

    usleep(1);/*子线程会打印两次
                 因为子线程并不是边输出边清空，而是输出玩之后再清空
                 在子线程输出完成后，此时主线程关闭标准输出会再刷新缓存区，因此有两次
    */
    return 0;
}
