#include <func.h>

int tcpInit( int* Fd, char* addr, char* port )
{ 
    int socketFd = socket( AF_INET, SOCK_STREAM, 0);
    ERROR_CHECK( socketFd, -1, "socket" );

    int ret;
    int reuse = 1;
    ret = setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));

    struct sockaddr_in serverAddr;
    bzero( &serverAddr, sizeof(serverAddr) );
    serverAddr.sin_family = AF_INET;
    short nport = atoi(port);
    serverAddr.sin_port = nport;
    serverAddr.sin_addr.s_addr = inet_addr(addr);
    ret = bind( socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr) );
    ERROR_CHECK( ret, -1, "bind" );

    ret = listen( socketFd, 0);
    ERROR_CHECK( ret, -1, "listen" );

    *Fd = socketFd;

    return 0;
}

int main( int argc, char* argv[] )
{
    ARGS_CHECK( argc, 3 );

    int socketFd;
    tcpInit( &socketFd, argv[1], argv[2] );

    struct sockaddr_in clientAddr;
    bzero( &clientAddr, sizeof(struct sockaddr_in) );
    int addrLen = sizeof(clientAddr);
    int newFd = accept( socketFd, (struct sockaddr*)&clientAddr, &addrLen );
    printf( "client ip = %s, client port = %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port) );
    ERROR_CHECK( newFd, -1, "accept" );

    int readFdNums, ret;
    char buf[128] = {0};
    while(1)
    {
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(newFd, &fds);
        FD_SET(socketFd, &fds);

        readFdNums = select( newFd+1, &fds, NULL, NULL, NULL );
        if (readFdNums > 0){
            if ( FD_ISSET(STDIN_FILENO, &fds) )
            {
                memset( buf, 0, sizeof(buf) ); 
                ret = read(STDIN_FILENO, buf, sizeof(buf) - 1); //避免越界
                ret = send( newFd, buf, strlen(buf)-1, 0 );
            }

            if ( FD_ISSET(newFd, &fds) )
            {
                memset( buf, 0, sizeof(buf) ); 
                ret = recv( newFd, buf, sizeof(buf), 0);
                if (ret == -1)
                {
                    printf("recv fail\n");
                    close(newFd);
                    break;
                }
                if (ret == 0)
                {
                    printf("byebye\n");
                    close(newFd);
                    break;
                }
                printf("%s\n", buf);
            }

            if ( FD_ISSET(socketFd, &fds) )
            {
                printf("新的连接来了\n");
            }

        }else{
        }

    }

    printf("跳出循环\n");

    close( newFd );
    close( socketFd);

    return 0;
}
