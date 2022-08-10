#include <func.h>

// 测试发现，值为一样的

void test1()
{
    struct sockaddr s1;
    struct sockaddr_in s2;

    printf("大小分别是：%ld, %ld \n", sizeof(s1), sizeof(s2) );
    printf("直接算结构体，大小分别是：%ld, %ld \n", sizeof(struct sockaddr), sizeof(struct sockaddr_in) );

    printf("-----------------\n");
    bzero( &s1, sizeof(s1) );
    bzero( &s2, sizeof(s2) );
    printf("清理后大小分别是：%ld, %ld \n", sizeof(s1), sizeof(s2) );
    printf("直接算结构体，大小分别是：%ld, %ld \n", sizeof(struct sockaddr), sizeof(struct sockaddr_in) );
}

int main()
{
    test1();

    return 0;
}
