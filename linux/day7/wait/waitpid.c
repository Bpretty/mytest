#include <func.h>

int main()
{
    pid_t ret = fork();
    if (ret==0){
        printf("i am child process, pid =%d, ppid=%d\n", getpid(), getppid());
        
        sleep(5);
        printf("end  child process \n");
        exit(5);
    }else{
        printf("i am parent process, ret=%d, pid=%d\n", ret, getpid());

        int status;
        pid_t pWid = waitpid(ret, &status, 0);
        printf("返回值是: %d\n", pWid);


        if (WIFEXITED(status)){
            printf("正常结束\n");
        }else{
            printf("异常结束\n");
        }

        printf("状态码是:%d\n", status);
    }
}
