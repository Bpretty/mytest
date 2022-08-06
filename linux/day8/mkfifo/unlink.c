#include <func.h>

int main( int argc, char* argv[])
{
    int ret = unlink( argv[1] );   

    if (-1==ret){
        printf("删除失败");
        return -1;
    }

    return 0;
}
