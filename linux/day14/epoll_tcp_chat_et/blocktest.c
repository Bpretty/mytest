#include <func.h>

void setBlock(int fd)
{
   int status = fcntl(fd, F_GETFL); 
   status = status|O_NONBLOCK;
   fcntl(fd, F_SETFL, status);
}

int main()
{
    char buf[128] = {0};
    int ret = read(STDIN_FILENO, buf, sizeof(buf));
    setBlock(STDIN_FILENO);
    sleep(5);
    printf("ret = %d, errno=%d\n", ret, errno);
    return 0;
}
