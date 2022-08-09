#include <func.h>

// 静态局部变量测试，验证ctime线程不安全

int main()
{
    time_t now;
    now = time(NULL);
    char* p1= ctime(&now);
    printf("time1 = %s\n", p1);

    sleep(3);

    now = time(NULL);
    char* p2= ctime(&now);
    printf("time2 = %s\n", p2);

    printf(" again, time1 = %s\n", p1);
    return 0;
}
