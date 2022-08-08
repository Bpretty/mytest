#include <func.h>

void sigFunc(int sigNum, siginfo_t* p, void* p1)
{
    printf("%d is comming \n", sigNum);
}

int main()
{

    struct sigaction act;
    bzero(&act, sizeof(act));
    act.sa_sigaction = sigFunc;
    act.sa_flags = SA_SIGINFO|SA_RESETHAND;
    sigaction(SIGINT, &act, NULL);

    while(1);

    return 0;
}
