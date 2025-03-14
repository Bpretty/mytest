#include <func.h>

int main( int argc, char* argv[])
{
    ARGS_CHECK(argc, 2);
    struct in_addr addr;
    
    int ret = inet_aton(argv[1], &addr);
    printf("%x\n", addr.s_addr);
    printf("%s\n", inet_ntoa(addr));    //网络字节序转为点分十进制
    printf("%x\n", inet_addr(argv[1])); //点分十进制转为网络字节序的整数

    return 0;
}
