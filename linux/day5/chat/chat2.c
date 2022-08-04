#include <func.h>

int main( int argc, char* argv[])
{
    if ( argc != 3){
        printf("参数错误，%d", argc);
        return -1;
    }

    int fdR, fdW;
    printf("00\n");
    fdW = open(argv[1],O_WRONLY );
    //printf("11\n");
    fdR = open(argv[2],O_RDONLY );
    //printf("22\n");
    int ret = 0;
    char buff[128] = {0};

    fd_set fds;
    while(1)
    {
        FD_ZERO(&fds);
        FD_SET( STDIN_FILENO, &fds );
        FD_SET(fdR, &fds);

        int nNums = select( fdR+1, &fds, NULL, NULL, NULL  );
        if (nNums > 0)
        {
            if (FD_ISSET(STDIN_FILENO, &fds))
            {
                memset(buff, 0, sizeof(buff));
                ret = read(STDIN_FILENO, buff, sizeof(buff) );
                if (ret ==0)
                {
                    printf("退出标准输入，关闭聊天\n");
                    break;
                }
                //ret = read(STDIN_FILENO, buff, strlen(buff)-1 );
                //printf("从标准输入读取字符：%d\n", ret);
                write( fdW, buff, strlen(buff)-1 );
            }

            if (FD_ISSET(fdR, &fds))
            {
                memset( buff, 0, sizeof(buff) );
                ret = read(fdR, buff, sizeof(buff) );
                if (ret ==0)
                {
                    printf("再见\n");
                    break;
                }
                //printf( "ret = %d, buff =%s",ret, buff );
                printf("%s\n", buff);
            }
        }

   }
}
