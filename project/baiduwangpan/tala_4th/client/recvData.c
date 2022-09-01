#include "head.h"
int recvData(int socketFd,char *p,int len)
{
    int totalSend = 0;
    int recvLen;
    while(totalSend < len)
    {
        recvLen = recv(socketFd,p + totalSend,len - totalSend,0);
        ERROR_CHECK(recvLen,-1,"recv");
        totalSend += recvLen;
    }
    return 0;
}

