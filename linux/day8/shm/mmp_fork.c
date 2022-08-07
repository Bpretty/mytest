#include <func.h>

int main()
{
    int fd = open("file", O_RDWR);
    char * p = (char*)mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if ( !fork() ){    //子进程

        printf("buf = %s\n", p);
    }else{          //父进程
        strcpy(p, "xiaozhizhi");

        wait(NULL);
    }

    return 0;
}
