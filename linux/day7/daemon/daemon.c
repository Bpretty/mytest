#include <func.h>

int myDaemon()
{
    if (fork())
    {
        printf("父进程：pid=%d\n", getpid());
        exit(1);
    }

    printf("子进程：pid=%d, ppid=%d\n", getpid(), getppid());
    //接下来是子进程
    setsid();
    chdir("/");
    umask(0);
    
    for( int i = 0; i<3; i++ ){
        close(i);
    }
}

int main()
{
    myDaemon();

    while(1);

    return 0;
}
