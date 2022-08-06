#include <func.h>

// fork的子进程相当于父进程的分身，也会走到main函数的打印语句
// 父进程中return只是返回函数调用点，进程并未退出，因此也会打印

int f()
{
    pid_t ret = fork();
    if (ret==0){
        printf("i am child process, pid =%d, ppid=%d\n", getpid(), getppid());
    }else{
        printf("i am parent process, ret=%d, pid=%d\n", ret, getpid());
        //exit(0); // 如果此处退出则不会走到主函数中的打印语句
        return 0;
    }
}

int main()
{
    f();

    //sleep(3);
    printf("走到main最后的进程是：%d\n", getpid() );
}
