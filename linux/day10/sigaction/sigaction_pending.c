#include <func.h>


void sigFunc(int sigNum, siginfo_t* p, void* p1)
{
    printf("begin %d is comming \n", sigNum);
    sleep(3);
    sigset_t pending;
    sigpending(&pending);
    if (sigismember(&pending, SIGQUIT)){
        printf(" sigquit is pending\n");
    }else{
        printf(" sigquit  is not pending\n");
    }

    printf("end %d is comming \n", sigNum);
}

int main()
{

    struct sigaction act;
    bzero(&act, sizeof(act));
    act.sa_sigaction = sigFunc;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT);
    sigaction(SIGINT, &act, NULL);

    while(1);

    return 0;
}
