#include <func.h>

#define N 10000000

// 使用mmap累加值打印的时候出现段错误，问题待看

int main()
{
    int shmid = shmget(1000, 4096, 0600|IPC_CREAT);
    printf("shmid=%d\n", shmid);

    int *p = (int*)shmat(shmid, NULL, 0);
    if ((int*)-1 == p){
        printf("shmat失败\n");
        return -1;
    }
    *p = 0;
    int i=0;

    int semArray = semget(1000, 1, IPC_CREAT|0600);
    int ret;
    ret = semctl(semArray, 0, SETVAL, 1);
    struct sembuf sopp, sopv;
    sopp.sem_num = 0;
    sopp.sem_op = -1;
    sopp.sem_flg = SEM_UNDO;
    sopv.sem_num = 0;
    sopv.sem_op = 1;
    sopv.sem_flg = SEM_UNDO;

    if ( !fork() ){    //子进程

        for( i =0; i<N; i++)
        {
            semop(semArray, &sopp, 1);
            *p+=1;
            semop(semArray, &sopv, 1);
        }
    }else{          //父进程
        for( i =0; i<N; i++)
        {
            semop(semArray, &sopp, 1);
            *p+=1;
            semop(semArray, &sopv, 1);
        }

        wait(NULL);
        printf("累计和为: %d \n", *p);
    }

    return 0;
}
