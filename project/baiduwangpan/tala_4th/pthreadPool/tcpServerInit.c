#include "head.h"

int tcpServerInit(int *sfd, char *ip, char *port)
{
    int sockfd = socket(AF_INET,SOCK_STREAM ,0);
    struct sockaddr_in serAddr;
    memset(&serAddr,0,sizeof(serAddr));
    serAddr.sin_family = AF_INET;
    serAddr.sin_addr.s_addr = inet_addr(ip);
    serAddr.sin_port = htons(atoi(port));
    int ret = bind(sockfd, (struct sockaddr *)&serAddr,sizeof(serAddr));
    ERROR_CHECK(ret ,-1, "bind");
    ret = listen(sockfd, 10);
    ERROR_CHECK(ret, -1, "listen");
    *sfd = sockfd;
    return 0; 
}

