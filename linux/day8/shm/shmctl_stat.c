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

    struct shmid_ds buf;
    int ret = shmctl( shmid, IPC_STAT, &buf );

    if (-1== ret){
        printf("连接失败\n");
        return -1;
    }

    printf("uid = %d\n", buf.shm_perm.uid);

    // 进程结束，解除本进程的连接
}
