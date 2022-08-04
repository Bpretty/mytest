#include <func.h>

int a = 1;
int main()
{
    pid_t ret = fork();
    if (ret==0){
        printf("i am child process, pid =%d, ppid=%d\n", getpid(), getppid());
        printf("a=%d\n", a);
    }else{
        printf("i am parent process, ret=%d, pid=%d\n", ret, getpid());

        a = 2;
        sleep(5);
    }
}
