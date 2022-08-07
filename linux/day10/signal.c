#include <func.h>

void sigFunc(int signum)
{
    printf("%d is comming \n", signum);
}

int main()
{
    if (SIG_ERR == signal(2, sigFunc)){
        printf("信号注册错误\n");
        return -1;
    }

    while(1);

    return 0;
}
