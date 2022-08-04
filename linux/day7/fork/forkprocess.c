#include <func.h>

int main()
{
    pid_t ret = fork();
    if (ret==0){
        printf("i am child process, pid =%d, ppid=%d\n", getpid(), getppid());
    }else{
        printf("i am parent process, ret=%d, pid=%d\n", ret, getpid());
        sleep(10);
    }
}
