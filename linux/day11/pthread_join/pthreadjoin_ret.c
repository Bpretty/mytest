#include <func.h>

void* func( void * p )
{
    char *pStr = (char*)malloc(128);
    strcpy( pStr, "i am ling\n");
    return pStr;
}

int main()
{
    pthread_t threadid;
    int ret = pthread_create(&threadid, NULL, func, NULL );
    if (ret!=0){
        printf("线程创建失败\n");
        return -1;
    }

    char* pStr ;
    pthread_join( threadid, (void**)&pStr );
    printf("返回值是：%s\n", pStr );

    return 0;
}
