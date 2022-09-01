#include "head.h"
int transmitData(int newFd,char *md5,char *filename)
{
    int ret;
    //定义小火车
    train t;
    //获取文件信息
    char buf[1000] = {0};
    sprintf(buf,"%s%s",DEFAULT_PATH,md5);
    printf("file real path %s\n",buf);
    struct stat fileStat;
    int fd = open(buf,O_RDONLY);
    ERROR_CHECK(fd,-1,"open");
    fstat(fd,&fileStat);
    //1.发送文件名
    t.dataLen = strlen(filename);
    strcpy(t.buf,filename);
    ret =sendData(newFd,(char *)&t,4 + t.dataLen);
    if(-1 == ret)
    {
        return -1;
    }
    //2.发送文件长度
    t.dataLen = sizeof(fileStat.st_size);
    memcpy(t.buf,&fileStat.st_size,sizeof(fileStat.st_size));
    ret = sendData(newFd,(char *)&t,4 + t.dataLen);

    if(-1 == ret)
    {
        return -1;
    }
    //3.发送文件内容
    while((t.dataLen = read(fd,t.buf,sizeof(t.buf))) > 0)
    {
        ret = sendData(newFd,(char *)&t,4 + t.dataLen);    
        if(-1 == ret)
        {
            return -1;
        }
    }
    //4.发送结束标志, t.datalen = 0,只发送4个字节(sizeof(t.dataLen)),因为sizeof(t.buf) = 0
    sendData(newFd,(char *)&t,4);
    return 0;
}
