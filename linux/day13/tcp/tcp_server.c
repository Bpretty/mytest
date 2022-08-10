#include <func.h>

int main( int argc, char* argv[] )
{
    ARGS_CHECK( argc, 3 );
    int socketFd = socket( AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK( socketFd, -1, "socket" );

    struct sockaddr_in serverAddr;
    bzero( &serverAddr, sizeof(serverAddr) );
    serverAddr.sin_family = AF_INET;
    short nport = atoi(argv[2]);
    serverAddr.sin_port = nport;
    serverAddr.sin_addr.s_addr = inet_addr( argv[1] );
    int ret = bind( socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr) );
    ERROR_CHECK( ret, -1, "bind" );

    ret = listen( socketFd, 0);
    ERROR_CHECK( ret, -1, "listen" );

    struct sockaddr_in clientAddr;
    bzero( &clientAddr, sizeof(struct sockaddr_in) );
    int addrLen = sizeof(clientAddr);
    int newFd = accept( socketFd, (struct sockaddr*)&clientAddr, &addrLen );
    printf( "client ip = %s, client port = %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port) );
    ERROR_CHECK( newFd, -1, "accept" );

    printf("客户端连接le\n");
    char buf[129] = {0};
    ret = recv( newFd, buf, sizeof(buf), 0 );
    printf("接收到%d个数据, 数据为：%s\n", ret, buf);
    ret = send( newFd, "world", 5, 0 );
    printf("发送了%d个数据\n", ret);

    close( newFd );
    close( socketFd);

    return 0;
}
