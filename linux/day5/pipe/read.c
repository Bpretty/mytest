#include <func.h>

int main()
{
    char buff[128] = {0};
    //int ret = read(STDIN_FILENO, buff, strlen(buff)-1 );
    int ret = read(STDIN_FILENO, buff, sizeof(buff) );
    printf("ret = %d, buff = %s\n", ret, buff);
    return 0;
}
