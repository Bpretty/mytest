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

    int epfd = epoll_create(1);
    struct epoll_event evt, evs[3];
    evt.events = EPOLLIN;
    evt.data.fd = socketFd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, socketFd, &evt );
    evt.data.fd = STDIN_FILENO;
    epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &evt );

    int readFdNums, ret;
    int i = 0;
    int newFd;
    char buf[128] = {0};
    struct sockaddr_in clientAddr;
    while(1)
    {
        readFdNums = epoll_wait( epfd, evs, 3, -1 );
        for(i=0; i< 3;i++)
        {

            if ( evs[i].data.fd == STDIN_FILENO )
            {
                memset( buf, 0, sizeof(buf) ); 
                ret = read(STDIN_FILENO, buf, sizeof(buf) - 1); //避免越界
                if (ret == 0)
                {
                    printf("服务端自己断开\n");
                    goto end;
                }
                ret = send( newFd, buf, strlen(buf)-1, 0 );
            }

            if ( evs[i].data.fd == newFd )
            {
                printf("newFd 可读\n");
                memset( buf, 0, sizeof(buf) ); 
                ret = recv( newFd, buf, sizeof(buf), 0);
                if (ret == 0)
                {
                    // 
                    evt.events = EPOLLIN;
                    evt.data.fd = newFd;
                    ret = epoll_ctl( epfd, EPOLL_CTL_DEL, newFd, &evt );
                    ERROR_CHECK(ret, -1, "epoll_del");
                    close(newFd);

                    printf("byebye\n");

                    break;
                }
                printf("%s\n", buf);
            }

            if (evs[i].data.fd == socketFd)
            {
                printf("新的连接来了\n");
                bzero( &clientAddr, sizeof(struct sockaddr_in) );
                int addrLen = sizeof(clientAddr);
                newFd = accept( socketFd, (struct sockaddr*)&clientAddr, &addrLen );
                printf( "client ip = %s, client port = %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port) );
                ERROR_CHECK( newFd, -1, "accept" );

                evt.data.fd = newFd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, newFd, &evt );
            }
        }
    }

end:
    close( newFd );
    close( socketFd);

    return 0;
}
