#include"factory.h"

void pthreadExit(void *p)
{
    pthread_exit(0);
}
void * complexInstruct(void *p)
{
    pFactory pf = (pFactory)p;
    pWorkQueue pwq = &pf->workQueue;
    //MYSQL *conn = mysqlConnInit();
    pNode tmpNode;
    int newFd;
    int ret;
    int len;
    off_t filesize;
    char *res;
    char filename[30];
    char objPath[256];
    char username[30];
    char md5[40];
    int precode;
    int flag = 1;
    while(1)
    {
        pthread_mutex_lock(&pwq->lock);
        if(!pwq->queueSize)
        {
            pf->waitNum++;
            pthread_cond_wait(&pf->cond,&pwq->lock);
            pf->waitNum--;
        }
        if(1 == pf-> endFlag)
        {
            pthread_mutex_unlock(&pwq->lock);
            pthread_exit(0);
        }
        ret = workQueuePop(&pf->workQueue,&tmpNode);
        pthread_mutex_unlock(&pwq->lock);
        if(-1 != ret)
        {
            memset(objPath,0,sizeof(objPath));
            memset(username,0,sizeof(username));
            sendData(tmpNode->sockFd,(char *)&flag,sizeof(int));
            recvData(tmpNode->sockFd,(char *)&len,sizeof(int));
            recvData(tmpNode->sockFd,objPath,len);
            recvData(tmpNode->sockFd,(char *)&len,sizeof(int));
            recvData(tmpNode->sockFd,username,len);
            //判断类型
            if(GETS == tmpNode->insType)
            {
                //检索并发送文件
                memset(filename,0,sizeof(filename));
                recvData(tmpNode->sockFd,(char *)&len,sizeof(int));
                recvData(tmpNode->sockFd,filename,len);
                printf("filename %s\n",filename);
                precode = getsFunc(conn,tmpNode->sockFd,username,objPath,filename);
                if(-1 == precode)
                {
                    res = "Error path\n";
                }else{
                    if(-2 == precode)
                    {
                        res = "Error file have already existes\n";
                    }else{
                        res = lsFunc(conn,username,objPath);
                    }
                }
                sendString(tmpNode->sockFd,res);
                printf("res : %s\n",res);
                free(tmpNode);
                close(newFd);
                //断开连接
            }else{
                //检索并接收文件
                memset(filename,0,sizeof(filename));
                memset(md5,0,sizeof(md5));
                //文件名
                recvData(tmpNode->sockFd,(char *)&len,sizeof(int));
                recvData(tmpNode->sockFd,filename,len);
                printf("filename %s\n",filename);
                //文件大小
                recvData(tmpNode->sockFd,(char *)&len,sizeof(int));
                recvData(tmpNode->sockFd,(char *)&filesize,len);
                printf("filesize %ld\n",filesize);
                //文件MD5
                recvData(tmpNode->sockFd,(char *)&len,sizeof(int));
                recvData(tmpNode->sockFd,md5,len);
                printf("md5 %s\n",md5);
                precode = putsFunc(conn,tmpNode->sockFd,username,objPath,filename,md5,filesize);
                if(-1 == precode)
                {
                    res = "Error path\n";
                }else{
                    if(-2 == precode)
                    {
                        res = "Error file have already existes\n";
                    }else{
                        res = lsFunc(conn,username,objPath);
                    }
                }
                sendString(tmpNode->sockFd,res);
                printf("res : %s\n",res);
                free(tmpNode);
                close(newFd);
                //断开连接
            }
            if(1 == pf-> endFlag)
            {
                mysql_close(conn);
                pthread_exit(0);
            }
        }        
    }
}
void * simpleInstruct(void *p)
{
    pFactory pf = (pFactory)p;
    pWorkQueue pwq = &pf->workQueue;
    pNode tmpNode;

    //MYSQL *conn = mysqlConnInit();
    int newFd;
    int ret;
    int len;
    int precode;
    char *res;
    char filename[30];
    char objPath[256];
    char username[30];
    int flag = 1;
    while(1)
    {
        pthread_mutex_lock(&pwq->lock);
        if(!pwq->queueSize)
        {
            pf->waitNum++;
            pthread_cond_wait(&pf->cond,&pwq->lock);
            pf->waitNum--;
        }
        if(1 == pf-> endFlag)
        {
            pthread_mutex_unlock(&pwq->lock);
            pthread_exit(0);
        }
        ret = workQueuePop(&pf->workQueue,&tmpNode);
        printf("ret = %d,newFd = %d,type = %d\n",ret,tmpNode->sockFd,tmpNode->insType);
        pthread_mutex_unlock(&pwq->lock);
        if(-1 != ret)
        {
            //发送开始信号
            memset(objPath,0,sizeof(objPath));
            memset(username,0,sizeof(username));
            sendData(tmpNode->sockFd,(char *)&flag,sizeof(int));
            recvData(tmpNode->sockFd,(char *)&len,sizeof(int));
            recvData(tmpNode->sockFd,objPath,len);
            recvData(tmpNode->sockFd,(char *)&len,sizeof(int));
            recvData(tmpNode->sockFd,username,len);
            switch(tmpNode->insType)
            {
            case 0:;break;//rm
            case 1:;break;//mv
            case 2:
                   //接路径
                   precode = cdFunc(conn,username,objPath);
                   if(-1 == precode)
                   {
                       res = "Error path\n";
                   }else{
                       res = lsFunc(conn,username,objPath);
                   }
                   sendString(tmpNode->sockFd,res);
                   break;//cd
            case 3:
                   memset(filename,0,sizeof(filename));
                   recvData(tmpNode->sockFd,(char *)&len,sizeof(int));
                   recvData(tmpNode->sockFd,filename,len);
                   precode = mkdirFunc(conn,username,filename,objPath);
                   if(-1 == precode)
                   {
                       res = "Error path\n";
                   }else{
                       if(-2 == precode)
                       {
                           res = "Error file have already existes\n";
                       }else{
                           res = lsFunc(conn,username,objPath);
                       }
                   }
                   sendString(tmpNode->sockFd,res);
                   printf("res : %s\n",res);
                   break;//mkdir
            case 4:res = lsFunc(conn,username,objPath);
                   sendString(tmpNode->sockFd,res);
                   break;//ls
            }
            //close(newFd);
            if(1 == pf-> endFlag)
            {
                mysql_close(conn);
                pthread_exit(0);
            }
        }        
    }
}
void * exitThread(void *p)
{
    printf("waiting for exit...\n");
    struct sigaction sig;
    sig.sa_flags = SA_SIGINFO;
    sig.sa_sigaction = factoryClose;
    sigaction(SIGUSR1,&sig,NULL);
    while(1)
    {
        //pthread_cleanup_push(pthreadExit,NULL);
        //pthread_cleanup_pop(0);
        if(1 == factory.endFlag)
        { 
            pthread_exit(0);       
        }
    }
}
void factoryInit(pFactory pf,int pthreadNum,int capacity)
{
    memset(pf,0,sizeof(factory_t));  
    pf->pthid = (pthread_t *)calloc(pthreadNum,sizeof(pthread_t));
    pf->pthreadNum = pthreadNum;
    int tmpCapacity = capacity;
    pf->waitNum = 0;
    pthread_cond_init(&pf->cond,NULL);
    workQueueInit(&(pf->workQueue),tmpCapacity);
}
void factoryStart(pFactory pf,int flag)
{
    int i;
    if(0 == pf->startFlag)
    {
        for(i = 0;i < pf->pthreadNum - 1;i++)
        {
            if(1 == flag)
            {
                pthread_create(pf->pthid + i,NULL,complexInstruct,pf);
            }else{
                pthread_create(pf->pthid + i,NULL,simpleInstruct,pf);
            }
        }
        pthread_create(pf->pthid + i,NULL,exitThread,pf);
        pf->startFlag = 1;
    }
}
void factoryClose(int signum,siginfo_t *p1,void *p2)
{
    int i;
    pFactory pf;
    printf("signum %d,start closing\n",signum);
    pf =&factory;
    pf->endFlag = 1;
    while(pf->waitNum)
    {
        pthread_cond_signal(&pf->cond);
    }
    long ret;
    int pthid;
    for(i = 0;i < pf->pthreadNum-1;i++)
    {
        pthid = pthread_join(*(pf->pthid + i),(void **)&ret);
        printf("%d. child is exit,return %ld\n",i+1,ret);
    }
    pthread_cancel(*(pf->pthid + pf->pthreadNum-1));
    pthid = pthread_join(*(pf->pthid + i),(void **)&ret);
    printf("%d. recycle child is exit,return %ld\n",i+1,ret);
    exit(0);
}
