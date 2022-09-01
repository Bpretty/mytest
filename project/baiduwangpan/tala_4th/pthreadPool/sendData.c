#include "head.h"

int sendData(int newFd,char *p,int len)
{
    int totalSend = 0;
    int sendLen;
    while(totalSend < len)
    {
        sendLen = send(newFd,p + totalSend,len - totalSend,0);
        if(-1 == sendLen)
        {
            return -1;
        }
        totalSend += sendLen;
    }
    return 0;
}

