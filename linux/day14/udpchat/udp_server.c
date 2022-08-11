#include <func.h>

int main( int argc, char* argv[] )
{
    ARGS_CHECK( argc, 3 );

    int socketFd = socket( AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK( socketFd, -1, "socket" );

    int ret;
   // int reuse = 1;
   // ret = setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));

    struct sockaddr_in serverAddr;
    bzero( &serverAddr, sizeof(serverAddr) );
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons( atoi(argv[2]) );
    serverAddr.sin_addr.s_addr = inet_addr( argv[1] );
    ret = bind( socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr) );
    ERROR_CHECK( ret, -1, "bind" );

    int readFdNums;
    struct sockaddr_in clientAddr;
    char buf[128] = {0};

    int addrLen = sizeof(clientAddr);
    ret = recvfrom( socketFd, buf, sizeof(buf), 0, (struct sockaddr*)&clientAddr, &addrLen );
    printf( "client ip = %s, client port = %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port) );

    fd_set fds;
    while(1)
    {
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(socketFd, &fds);

        readFdNums = select( socketFd+1, &fds, NULL, NULL, NULL );
        if (readFdNums > 0){
            if ( FD_ISSET(STDIN_FILENO, &fds) )
            {
                //printf("读输入\n");
                memset( buf, 0, sizeof(buf) ); 
                ret = read(STDIN_FILENO, buf, sizeof(buf) - 1); //避免越界
                ret = sendto( socketFd, buf, strlen(buf)-1, 0, (struct sockaddr*)&clientAddr, sizeof(clientAddr) );
                //printf("服务端发送：%d个\n", ret);
                //printf( "发送的client ip = %s, client port = %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port) );
            }

            if ( FD_ISSET(socketFd, &fds) )
            {
                //printf("读socket\n");
                memset( buf, 0, sizeof(buf) ); 
                ret = recvfrom( socketFd, buf, sizeof(buf), 0, NULL, NULL );
                printf("%s\n", buf);
            }

        }else{
            if (readFdNums == -1)
            {
                printf("select fail\n");
                return -1;
            }
        }

    }

    printf("跳出循环\n");

    close( socketFd);

    return 0;
}
