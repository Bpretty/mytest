#include <func.h>

int main( int argc, char* argv[])
{
    if ( argc != 3){
        printf("参数错误，%d", argc);
        return -1;
    }

    int fdR, fdW;
    printf("begin\n");
    fdR = open(argv[1], O_RDONLY);
    //printf("aa\n");
    fdW = open(argv[2], O_WRONLY);
    //printf("bb\n");
    int ret = 0;

    char buff[128] = {0};
    while(1)
    {
        memset( buff, 0, sizeof(buff) );
        ret = read(fdR, buff, sizeof(buff) );
        //printf( "ret = %d, buff =%s\n",ret, buff );
        printf("%s\n",buff);

        memset(buff, 0, sizeof(buff));
        ret = read(STDIN_FILENO, buff, sizeof(buff) );
        //printf("从标准输入读取字符：%d\n", ret);
        ret =write( fdW, buff, strlen(buff)-1 );
        //printf("写入管道字符%d", ret);
    }
}
