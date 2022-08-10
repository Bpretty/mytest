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
    int newFd;

    int readFdNums, ret;
    //int maxFlag = newFd + 1;
    int maxFlag = 15;
    char buf[128] = {0};
    fd_set fds, originalFds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &originalFds);
    FD_SET(socketFd, &originalFds);

    while(1)
    {
        FD_ZERO(&fds);
        memcpy(&fds, &originalFds, sizeof(fd_set));

        readFdNums = select( maxFlag, &fds, NULL, NULL, NULL );
        if (readFdNums > 0){
            //printf("描述符有%d个可读的\n", readFdNums);

            if ( FD_ISSET(STDIN_FILENO, &fds) )
            {
                //printf("标准输入可读\n");
                memset( buf, 0, sizeof(buf) ); 
                ret = read(STDIN_FILENO, buf, sizeof(buf) - 1); //避免越界
                ret = send( newFd, buf, strlen(buf)-1, 0 );
            }

            if ( FD_ISSET(newFd, &fds) )
            {
                //printf("newFd可读\n");
                memset( buf, 0, sizeof(buf) ); 
                ret = recv( newFd, buf, sizeof(buf), 0);
                if (ret == 0)
                {
                    printf("byebye\n");
                    close(newFd);
                    FD_CLR(newFd, &originalFds);
                }else{
                    printf("%s\n", buf);
                }
            }

            if ( FD_ISSET(socketFd, &fds) )
            {
                printf("新的连接来了\n");

                bzero( &clientAddr, sizeof(struct sockaddr_in) );
                int addrLen = sizeof(clientAddr);
                newFd = accept( socketFd, (struct sockaddr*)&clientAddr, &addrLen );
                printf( "client ip = %s, client port = %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port) );
                ERROR_CHECK( newFd, -1, "accept" );
                
                FD_SET(newFd, &originalFds );
            }

        }else{
            if (readFdNums == -1)
            {
                printf("select失败\n");
                exit(-1);
            }
            printf("no value\n");
        }

    }

    printf("跳出循环\n");

    close( socketFd);

    return 0;
}
