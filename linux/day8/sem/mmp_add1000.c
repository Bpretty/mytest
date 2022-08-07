#include <func.h>

#define N 10000000

// 使用mmap累加值打印的时候出现段错误，原因是直接把指针和数值相加

int main()
{
    int fd = open("file", O_RDWR);
    if ( fd == -1){
        printf("打开文件失败\n");
        return -1;
    }
    int * p = (int*)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if ((int*)-1 == p){
        printf("mmap失败\n");
        return -1;
    }
    *p = 0;
    if ( !fork() ){    //子进程

        for(int i =0; i<=N; i++)
        {
            *p+=1;
        }
    }else{          //父进程
        for(int i =0; i<=N; i++)
        {
            *p+=1;
        }

        wait(NULL);
        printf("累计和为: %d \n", *p);
    }

    return 0;
}
