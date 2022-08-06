#include <func.h>

int main( int argc, char* argv[])
{
    int ret = mkfifo( argv[1], 0666 );   

    if (-1==ret){
        printf("创建失败");
        return -1;
    }

    return 0;
}
