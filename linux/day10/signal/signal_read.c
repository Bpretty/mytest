#include <func.h>

void sigFunc(int signum)
{
    printf(" before %d is comming \n", signum);
    sleep(3);
    printf(" after %d is comming \n", signum);
}

int main()
{
    if (SIG_ERR == signal(SIGINT, sigFunc)){
        printf("信号注册错误\n");
        return -1;
    }
    if (SIG_ERR == signal(SIGQUIT, sigFunc)){
        printf("信号注册错误\n");
        return -1;
    }

    char buf[128]={0};
    read(STDIN_FILENO, buf, sizeof(buf));
    printf("buf = %s\n", buf);
    
    return 0;
}
