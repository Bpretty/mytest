#include <func.h>

int main( int argc, char* argv[])
{
    if ( argc != 2){
        printf("参数错误，%d", argc);
        return -1;
    }

    int fdR;
    fdR = open(argv[1], O_RDONLY);
    int ret = 0;

    char buff[128] = {0};
//    while(1)
//    {

        memset(buff, 0, sizeof(buff));
        ret = read(STDIN_FILENO, buff, strlen(buff)-1 );
        printf("从标准输入读取字符：%d\n", ret);
        write( fdW, buff, sizeof(buff) );
//    }
}
