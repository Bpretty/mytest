#include <func.h>

void sigFunc(int signum)
{
    printf("%d is comming \n", signum);
}

int main()
{
    // 信号忽略
    if (SIG_ERR == signal(SIGINT, SIG_IGN)){
        printf("信号注册错误\n");
        return -1;
    }

    while(1);

    return 0;
}
