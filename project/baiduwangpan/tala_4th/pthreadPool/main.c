#include"factory.h"

typedef struct{
    int flag;
    char username[30];
    char ciphertext[100];
    char token[100];
    char *salt;
    char curPath[256];
}userInformation,pUserInf;
typedef struct{
    int type;
    int len;
    char instruct[256];
}command_t;
void sendString(int newFd,char *str)
{
    int len = strlen(str);
    sendData(newFd,(char *)&len,sizeof(int));
    sendData(newFd,str,len);
}
char * tokenGenerate(MYSQL *conn,char *username)
{
    char *q = "delete from token where username ='";
    char query[200] = {0};
    sprintf(query,"%s%s%s",q,username,"';");
    insertSql(conn,query);
    char *salt = saltGenerate();
    char *token = crypt(username,salt);
    char *q1 = "insert into token(username,user_token) values('";
    memset(query,0,sizeof(query));
    sprintf(query,"%s%s%s%s%s",q1,username,"','",token,"');");
    //printf("%s\n",query);
    insertSql(conn,query);
    return token;

}
//接收及验证登录信息
int recvInfor(int newFd,MYSQL *conn)
{
    int len;
    int res;
    userInformation user;
    memset(&user,0,sizeof(user));
    //接收标志位
    recvData(newFd,(char *)&user.flag,sizeof(int));
    //接收用户名
    recvData(newFd,(char *)&len,sizeof(int));
    recvData(newFd,(char *)&user.username,len);
    printf("****flag = %d,username = %s\n",user.flag,user.username);
    //判断flag
    if(0 == user.flag)
    {
        //用户没有token,查看用户名
        user.salt = getSalt(conn,user.username);
        if(NULL == user.salt)
        {
            res = ERROR_USERNAME;
            sendData(newFd,(char *)&res,sizeof(int));
            //close(newFd);
            return -1;
        }else{
            //发送salt 给 用户
            res = OPERATE_SUCCESS;
            sendData(newFd,(char *)&res,sizeof(int));
            sendString(newFd,user.salt);
            recvData(newFd,(char *)&len,sizeof(int));
            recvData(newFd,(char *)&user.ciphertext,len);
            int ret = verifyPassword(conn,user.username,user.ciphertext);
            if(-1 == ret)
            {
                res = ERROR_PASSWORD;
                sendData(newFd,(char *)&res,sizeof(int));
            }else{
                res = OPERATE_SUCCESS;
                sendData(newFd,(char *)&res,sizeof(int));
                //生成token返回给客户端
                char *token = tokenGenerate(conn,user.username);
                sendString(newFd,token);
            }
            return ret;
        }
        //验证token值
    }else{
        recvData(newFd,(char *)&len,sizeof(int));
        recvData(newFd,(char *)&user.token,len);
        int ret = verifyToken(conn,user.username,user.token);
        if(-1 == ret)
        {
            res = ERROR_PASSWORD;
            sendData(newFd,(char *)&res,sizeof(int));
        }else{
            res = OPERATE_SUCCESS;
            sendData(newFd,(char *)&res,sizeof(int));
        }
        return ret;
    }
}
    //连接池
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,5);
    int sockfd;
    tcpServerInit(&sockfd,argv[1],argv[2]);
    factoryInit(&factory,atoi(argv[3]),atoi(argv[4]));//
    factoryInit(&qFactory,2,atoi(argv[4]));//
    factoryStart(&factory,2);
    factoryStart(&qFactory,1);
    conn = mysqlConnInit();
    pWorkQueue sq = &factory.workQueue;
    pWorkQueue cq = &qFactory.workQueue;
    int fdNum = 1;
    int ret;
    int epfd = epoll_create(1);
    struct epoll_event event;
    struct epoll_event *evs;
    event.data.fd = sockfd;
    event.events = EPOLLIN;
    epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&event);

    evs = (struct epoll_event *)calloc(MAXFDNUM,sizeof(int));
    int readyNum;
    int i;
    int newFd = 0;
    int tmpFd;
    command_t ins;
    //存放监控的 fd 队列
    /*--------------workQueue_t fdQueue;
      workQueueInit(&fdQueue,MAXFDNUM);*/
    while(1)
    {
        readyNum = epoll_wait(epfd,evs,fdNum,-1);
        printf("readyNum = %d\n",readyNum);
        for(i = 0;i < readyNum;i++)
        {
            if(sockfd == evs[i].data.fd)
            { 
                newFd = accept(sockfd,NULL,NULL);
                //验证
                ret =recvInfor(newFd,conn);
                //通过则放入fd队列等待发来的命令（注册epoll）
                //根据命令type分类，(gets,puts)从队列清除放入子线程队列，其他命令主线程处理
                printf("------------result = %d\n",ret);
                if(0 == ret)
                {
                    fdNum++;
                    event.data.fd = newFd;
                    event.events = EPOLLIN;
                    epoll_ctl(epfd,EPOLL_CTL_ADD,newFd,&event);
                    if(fdNum > MAXFDNUM)
                    {    
                        evs = (struct epoll_event*)realloc(evs,2 * MAXFDNUM * sizeof(int));
                    }
                }
            }else{
                //直接else，因为不是sockfd触发就是newfd触发，主线程不必管是哪一个newfd
                memset(&ins,0,sizeof(ins));
                ins.type = -1;
                //接类型
                tmpFd = evs[i].data.fd;
                recvData(tmpFd,(char *)&ins.type,sizeof(int));
                //分类
                if(ins.type >= RM && ins.type <=PWD)
                {
                    //交给处理短命令的线程
                    //放进短命令任务队列
                    printf("get simple instruct\n");
                    pNode pNew = (pNode)calloc(1,sizeof(Node));
                    pNew->sockFd = tmpFd;
                    pNew->insType = ins.type;
                    pthread_mutex_lock(&sq->lock);
                    ret = workQueuePush(sq,pNew);
                    pthread_mutex_unlock(&sq->lock);
                    pthread_cond_signal(&factory.cond);
                    //close(tmpFd);//子线程中做这项！！！！：
                    //fdNum--;
                }else{
                    //长命令线程
                    epoll_ctl(epfd,EPOLL_CTL_DEL,tmpFd,&event);
                    printf("get complex instruct\n");
                    pNode pNew = (pNode)calloc(1,sizeof(Node));
                    pNew->sockFd = tmpFd;
                    pNew->insType = ins.type;
                    pthread_mutex_lock(&cq->lock);
                    ret = workQueuePush(cq,pNew);
                    pthread_mutex_unlock(&cq->lock);
                    pthread_cond_signal(&qFactory.cond);
                    //close(tmpFd);//在子线程中做这项！！！
                    //fdNum--;
                }
            }
        }

    }
    return 0;
}

