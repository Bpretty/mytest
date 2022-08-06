#include <func.h>

int main()
{
    int fds[2];
    pipe(fds);

    if ( fork() ){
        close(fds[0]);  // 关闭子进程读端

        char buf[128]={"hello! "};
        write(fds[1], buf, strlen(buf) );

        exit(0);
    }else{
        close(fds[1]);  // 关闭子进程写端

        char buf1[128] = {0};
        read(fds[0], buf1, sizeof(buf1) );

        printf("父进程读取: %s\n", buf1);

        wait(NULL);
    }

    // car! 一般来说读写结束后应当关闭描述符，这里进程直接结束了就不处理了
}
