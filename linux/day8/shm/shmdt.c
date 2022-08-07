#include <func.h>

int main()
{
    int shmid;
    shmid = shmget( 1000, 4096, 0600|IPC_CREAT ); //非4096会浪费物理页空间

    if (-1== shmid){
        printf("参数异常\n");
        return -1;
    }

    int *p = (int*)shmat(shmid, NULL, 0);
    if ( (int*)-1== p ){
       printf("连接失败\n");
       return -1;
    }

    int ret = shmdt( p );
    if (-1==ret){
       printf("解除映射失败\n");
       return -1;
    }

}
