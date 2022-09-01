#include "head.h"

int recvFile(int socketFd,char * md5,long filesize)
{
    //接收文件
    int ret;
    int fd;
    int dataLen;
    char buf[1000] = {0};
    long downloadSize = 0;
    long fileSize = filesize;
    time_t now,lastSec;
    sprintf(buf,"%s%s",DEFAULT_PATH,md5);
    printf("file real path %s\n",buf);
    //.!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!错误
    fd = open(buf,O_CREAT|O_RDWR,0666);
    now = lastSec = time(NULL);
    while(1)
    {
        ret = recvData(socketFd,(char *)&dataLen,sizeof(int));
        if(-1 == ret)
        {
            close(socketFd);
            return -1;
        }
        if(dataLen)
        {
            memset(buf,0,sizeof(buf));
            ret = recvData(socketFd,buf,dataLen);
            if(-1 == ret)
            {
                close(socketFd);
                return -1;
            }
            write(fd,buf,dataLen);
            downloadSize+=dataLen;
            now = time(NULL);
            if(now - lastSec >= 0.5)
            {
                printf("\rcurrent progress:%5.2f%%",(float)downloadSize/fileSize*100);
                fflush(stdout);
                lastSec = now;
            }
        }else{                  
            printf("\rcomplete:100%%                ");
            close(fd);
            close(socketFd);
            break;
        }
    }
    printf("\n");
    return 0;
}

