#include <func.h>


int main( int argc, char* argv[] )
{
    ARGS_CHECK( argc, 3 );
    int socketFd = socket( AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK( socketFd, -1, "socket" );

    struct sockaddr_in serverAddr;
    bzero( &serverAddr, sizeof(serverAddr) );
    serverAddr.sin_family = AF_INET;
    short nport = atoi( argv[2] );
    serverAddr.sin_port = nport;
    serverAddr.sin_addr.s_addr = inet_addr( argv[1] );

    int ret = connect( socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr) );
    ERROR_CHECK( ret, -1, "bind" );

    ret = send( socketFd, "hello", 5, 0 );
    printf("发送%d个字节\n", ret);
    char buf[128] = {0};
    ret = recv( socketFd, buf, sizeof(buf), 0 );
    printf("接收到%d个字节, 数据为：%s\n", ret, buf);

    close( socketFd);

    return 0;
}
