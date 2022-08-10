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
    ERROR_CHECK( ret, -1, "connect" );

    printf("连接成功，准备监听描述符\n");

    int readFdNums;
    char buf[128] = {0};
    fd_set fds;
    while(1)
    {
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(socketFd, &fds);

        readFdNums = select( socketFd+1, &fds, NULL, NULL, NULL );
        if (readFdNums > 0){
            //printf("有描述符\n");
            if ( FD_ISSET(STDIN_FILENO, &fds) )
            {
                //printf("标准输入\n");
                memset( buf, 0, sizeof(buf) ); 
                ret = read(STDIN_FILENO, buf, sizeof(buf) - 1); //避免越界
                ret = send( socketFd, buf, strlen(buf)-1, 0 );
            }

            if ( FD_ISSET(socketFd, &fds) )
            {
                //printf("socket可读\n");
                memset( buf, 0, sizeof(buf) ); 
                ret = recv( socketFd, buf, sizeof(buf), 0);
                if (ret ==0)
                {
                    printf("buy\n");
                    break;
                }
                printf("%s\n", buf);
            }
       }else{
        }

   }
 
    close( socketFd);

    return 0;
}
