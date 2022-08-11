#include <func.h>


int main( int argc, char* argv[] )
{
    ARGS_CHECK( argc, 3 );
    int socketFd = socket( AF_INET, SOCK_DGRAM, 0);
    ERROR_CHECK( socketFd, -1, "socket" );

    struct sockaddr_in serverAddr;
    bzero( &serverAddr, sizeof(serverAddr) );
    serverAddr.sin_family = AF_INET;
    short nport = atoi( argv[2] );
    serverAddr.sin_port = htons(nport);
    serverAddr.sin_addr.s_addr = inet_addr( argv[1] );

    int ret;
    char buf[128] = {0};
    sendto( socketFd, buf, 1, 0,  (struct sockaddr*)&serverAddr, sizeof(serverAddr) );

    fd_set fds;
    int readFdNums;
    while(1)
    {
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(socketFd, &fds);

        readFdNums = select( socketFd+1, &fds, NULL, NULL, NULL );
        if (readFdNums > 0){
            if ( FD_ISSET(STDIN_FILENO, &fds) )
            {
                //printf("客户端输入可读\n");
                memset( buf, 0, sizeof(buf) ); 
                ret = read(STDIN_FILENO, buf, sizeof(buf) - 1); //避免越界
                ret = sendto( socketFd, buf, strlen(buf)-1, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr) );
                //printf( "server ip = %s, server port = %d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port) );
                //printf("客户端发送: %d个", ret);
            }

            if ( FD_ISSET(socketFd, &fds) )
            {
                //printf("客户端socket可读\n");
                memset( buf, 0, sizeof(buf) ); 
                ret = recvfrom( socketFd, buf, sizeof(buf), 0, NULL, NULL );
                printf("%s\n", buf);
            }
       }else{
        }

   }
 
    close( socketFd);

    return 0;
}
