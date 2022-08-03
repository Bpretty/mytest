#include <func.h>

int main( int argc, char* argv[])
{
    if ( argc != 3){
        printf("参数错误，%d", argc);
        return -1;
    }

    int fdR, fdW;
    fdR = open(argv[1], O_RDONLY);
    fdW = open(argv[2], O_WRONLY);
    int ret = 0;

    char buff[128] = {0};
//    while(1)
//    {
        memset( buff, 0, sizeof(buff) );
        ret = read(fdR, buff, sizeof(buff) );
        printf( "ret = %d, buff =%s",ret, buff );

        memset(buff, 0, sizeof(buff));
        printf("标准输入描述符值：%d\n", STDIN_FILENO);
        ret = read(STDIN_FILENO, buff, strlen(buff)-1 );
        printf("从标准输入读取字符：%d\n", ret);
        write( fdW, buff, sizeof(buff) );
//    }
}
