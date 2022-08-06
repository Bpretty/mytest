#include <func.h>

// 这里为何编译出错了??因为检查错了地方！！！

int f1()
{
    printf(" print function ");
    _exit(2);

    return 0;
}

int main()
{
    int pRet = fork();
    if (pRet == 0){
        printf("hello\n");

        //f1();

        _exit(1);
    }else{

        int status;
        int *b = &status;

        if (WIFEXITED(status)){
            printf("正常结束\n");
        }else{
            printf("异常结束\n");
        }

        printf("status的值为：%d\n", status);
    }
}
