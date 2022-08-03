#include <func.h>

int main( int argc, char* argv[])
{
    if ( argc != 2){
        printf("参数错误，%d", argc);
        return -1;
    }

    int fdW;
    fdW = open(argv[1],O_WRONLY );
    int ret = 0;

    char buff[128] = {0};
//    while(1)
//    {

        memset( buff, 0, sizeof(buff) );
        ret = read(fdW, buff, sizeof(buff) );
        printf( "ret = %d, buff =%s",ret, buff );

//   }
}
