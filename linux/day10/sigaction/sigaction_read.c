#include <func.h>

// 

void sigFunc(int sigNum, siginfo_t* p, void* p1)
{
    printf("%d is comming \n", sigNum);
}

int main()
{

    struct sigaction act;
    bzero(&act, sizeof(act));
    act.sa_sigaction = sigFunc;
    act.sa_flags = SA_SIGINFO|SA_RESTART;
    sigaction(SIGINT, &act, NULL);

    char buf[128] = {0};
    int ret = read(STDIN_FILENO, buf, sizeof(buf));
    if (-1==ret){
        printf("read fail\n");
        return -1;
    }

    printf("buf = %s\n", buf);

    return 0;
}
