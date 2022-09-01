#include "commandHandle.h"
#include"mysqlInit.h"
enum MSG{
    OPERATE_SUCCESS,
    ERROR_USERNAME,
    ERROR_PASSWORD,
    ERROR_PATH,
    NO_SUCH_FILE
};
enum commmandToken{
    RM,
    MV,
    CD,
    MKDIR,
    LS,
    PWD,
    GETS,
    PUTS,
    EXIT
};
typedef struct{
    command_t ins;
    char fileName[50];
    char fileSize[50];
    char addr[64];
    char port[32];
}complexCommand_t;
void tmpInformationInit()
{
    memset(&tmpInf,0,sizeof(tmpInformation));
    strcpy(tmpInf.curPath,"/");
}
int clientInit(int *sockfd ,char* addr,char *port)
{
    int socketFd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_addr.s_addr = inet_addr(addr);
    serverAddr.sin_port = htons(atoi(port));
    serverAddr.sin_family = AF_INET;
    int ret = connect(socketFd,(struct sockaddr *)&serverAddr,sizeof(struct sockaddr));
    ERROR_CHECK(ret,-1,"connect");
    *sockfd = socketFd;
    return 0;
}
void sendString(int newFd,char *str)
{
    int len = strlen(str);
    sendData(newFd,(char *)&len,sizeof(int));
    sendData(newFd,str,len);
}
int sendInfor(int newFd)
{
    int len;
    char salt[30];
    int res;
    int sfd = newFd;
    ///////////////////////////////////////////printf("flag = %d,un = %s,pwd = %s\n",tmpInf.flag,tmpInf.username,tmpInf.passwd);
    //先发送标志位
    sendData(sfd,(char *)&tmpInf.flag,sizeof(int));

    //在发送用户名
    sendString(sfd,tmpInf.username);

    //若已获得token则发送，否则发送密文
    if(1 == tmpInf.flag)
    {
        sendString(sfd,tmpInf.token);
        recvData(sfd,(char *)&res,sizeof(int));
        if(OPERATE_SUCCESS == res)
        {
            return 0;
        }else{
            sleep(3);
            tmpInformationInit();
            return -1;
        }
    }else{
        //没有token，则等待服务器发送salt
        recvData(sfd,(char *)&res,sizeof(int));
        //printf("res = %d\n",res);
        if(ERROR_USERNAME == res)
        {
            printf("error username\n");
            sleep(3);
            tmpInformationInit();
            return -1;
        }else{
            //得到盐值，加密，发送密文
            recvData(sfd,(char *)&len,sizeof(int));
            recvData(sfd,salt,len);
            //////////////////////////////////////////////////////////////////////////printf("salt = %s\n",salt);
            char *ciphertext = crypt(tmpInf.passwd,salt);
            sendString(sfd,ciphertext);        

            //等待结果
            recvData(sfd,(char *)&res,sizeof(int));
            if(OPERATE_SUCCESS == res)
            {
                //得到token值
                recvData(sfd,(char *)&len,sizeof(int));
                recvData(sfd,(char *)tmpInf.token,len);
                system("clear");
                //printf("token = %s\n",tmpInf.token);
                printf("login success\n");
                tmpInf.flag = 1;
                return 0;
            }else{
                printf("error password\n");
                sleep(3);
                tmpInformationInit();
                return -1;
            }
        }
    }
    //发送当前路径 (暂时不用，服务器一直保持连接)
}
// mkdir /path/dirname
// gets  /path/filename
// puts  /path/name
int pathCheck(const char *path)
{
    int len = strlen(path);
    if('/' == path[0])
    {
        if('/' == path[len - 1])
        {
            return 0;//无须拼接
        }else{
            return 1;//拼接 /
        }
    }else{
        if(!strncmp(path,"..",2))
        {
            return 2;//返回上一级
        }else{
            if(!strncmp(path,".",1))
            {
                return 3;//当前路径
            }else{
                return 4;//（拼接当前路径）+文件名 +/        
            }
        }
    }
}
int getPath(char *str[])
{
    int ret;
    while((*str)++)
    {
        if(' ' == (*str)[0] && ' ' != (*str)[1])
        {
            (*str)++;
            ret = pathCheck(*str);
            if(2 == ret)
            {
                if(!strcmp(tmpInf.curPath,"/"))
                {
                    ret = -1;
                }
            }
            break;
        }
    }
    return ret;
}

char * getFileName(const char *str)
{
    int len = strlen(str);
    char p[30] = {0};
    char p1[30] = {0};
    char *filename;
    int i;
    int j = 0;
    for(i = len - 2;i >= 0 && str[i] != '/';i--)
    {
        p[j++] = str[i];
    }
    len = strlen(p);
    for(i = len - 1,j = 0;i >= 0;i--)
    {
        p1[j++] = p[i];
    }
    filename = p1;
    return filename;

}
int downloadFile(int sfd,char *f,int t)
{
    int type = t;
    int newFd = sfd;
    int flag;
    int ret;
    int len;
    long filesize;
    char rcFilename[50] = {0}; 
    char *filename = f;
    sendData(newFd,(char *)&type,sizeof(int));
    recvData(newFd,(char *)&flag,sizeof(int));
    sendString(newFd,tmpInf.curPath);
    sendString(newFd,tmpInf.username);
    sendString(newFd,filename);
    //
    recvData(newFd,(char *)&len,sizeof(int));
    recvData(newFd,(char *)&rcFilename,len);
    recvData(newFd,(char *)&len,sizeof(int));
    recvData(newFd,(char *)&filesize,len);
    ret = recvFile(newFd,filename,filesize);
}
int uploadFile(int sfd,char *f,int t)
{
    int type = t;
    int newFd = sfd;
    int flag;
    int ret;
    char *filename = f;
    char md5Str[40] = {0};
    ret = Compute_file_md5(filename,md5Str);
    printf("-----------md5 %s\n",md5Str);
    if(-1 == ret)
    {
        printf("Error filename\n");
        return -1;
    }
    sendData(newFd,(char *)&type,sizeof(int));
    recvData(newFd,(char *)&flag,sizeof(int));
    sendString(newFd,tmpInf.curPath);
    sendString(newFd,tmpInf.username);
    ret = transmitFile(newFd,filename,md5Str);
}
int sendCommand(int newFd,command_t ins)
{
    int ret;
    int isReady;
    int flag;
    int len1;
    int len2;
    int len;
    char buf[1024] = {0};
    char path[1024] = {0};
    char *p = ins.instruct;
    char *filename;
    switch(ins.type)
    {
        case 0:;break;//rm
        case 1:;break;//mv
        case 2:ret = getPath(&p);
               len1 = strlen(p);
               p[len1 - 1] = '\0';
               //printf("ret = %d\n",ret);
               switch(ret)
               {
                    case 0:strcpy(path,p);//sendString(newFd,p);
                           break;
                    case 1:sprintf(path,"%s%s",p,"/");
                           //sendString(newFd,p);
                           break;
                    case 2:filename = getFileName(tmpInf.curPath);
                           len1 = strlen(filename) + 1;
                           len2 = strlen(tmpInf.curPath);
                           strncpy(path,tmpInf.curPath,len2 - len1);
                           break;
                    case 3:printf("Cur Dir\n");return -1;
                    case 4:sprintf(path,"%s%s%s",tmpInf.curPath,p,"/");break;
                    default:printf("Error,\"/\" is the top directory\n");return -1;
               }
               sendData(newFd,(char *)&ins.type,sizeof(int));
               recvData(newFd,(char *)&flag,sizeof(int));
               sendString(newFd,path);
               sendString(newFd,tmpInf.username);
               memset(tmpInf.curPath,0,sizeof(tmpInf.curPath));
               strcpy(tmpInf.curPath,path);
               break;//cd

        case 3:ret = getPath(&p);
               strncpy(path,p,strlen(p)-1);
               if(4 != ret)
               {
                   printf("Error filename\n");
                   return -1;
               }
               sendData(newFd,(char *)&ins.type,sizeof(int));
               recvData(newFd,(char *)&flag,sizeof(int));
               sendString(newFd,tmpInf.curPath);
               sendString(newFd,tmpInf.username);
               sendString(newFd,path);
               ;break;//mkdir

        case 4:sendData(newFd,(char *)&ins.type,sizeof(int));
               recvData(newFd,(char *)&flag,sizeof(int));
               sendString(newFd,tmpInf.curPath);//ls
               sendString(newFd,tmpInf.username);
               break;
        case 5:printf("Cur: %s\n",tmpInf.curPath);
               break;//pwd
        case 6:ret = getPath(&p);
               strncpy(path,p,strlen(p)-1);
               if(4 != ret)
               {
                   printf("Error filename\n");
                   return -1;
               }
               downloadFile(newFd,path,ins.type);
               recvData(newFd,(char *)&len,sizeof(int));
               recvData(newFd,buf,len);
               //system("clear");
               //printf("%s\n",buf);
               break;//gets
        case 7:ret = getPath(&p);
               strncpy(path,p,strlen(p)-1);
               if(4 != ret)
               {
                   printf("Error filename\n");
                   return -1;
               }
               uploadFile(newFd,path,ins.type);
               recvData(newFd,(char *)&len,sizeof(int));
               recvData(newFd,buf,len);
               system("clear");
               printf("%s\n",buf);

               break;//puts

    }
    return 0;
}
void * pthreadFunc(void *p)
{
    complexCommand_t *c = (complexCommand_t *)p;
    int newFd;
    int ret;

    int fd;//文件描述符
    char pathFrom[256] = {0};
    char pathTo[256] = {0};
    int flag;
    printf("***command：%s",c->ins.instruct);
    if(c->ins.type == PUTS)
    {
        //fd = open("");
        ret = clientInit(&newFd,c->addr,c->port);
        //子线程带着token登录
        sendInfor(newFd);
        sendCommand(newFd,c->ins);
        //发送文件信息
    }else{
        ret = clientInit(&newFd,c->addr,c->port);
        //子线程带着token登录
        sendInfor(newFd);
        sendCommand(newFd,c->ins);
        //接收文件信息
    }
    //recvData(newFd,(char *)&flag,sizeof(int));
    close(newFd);
    pthread_exit(0);
}
void pthreadInit(complexCommand_t *c)
{
    pthread_t pthread;
    pthread_create(&pthread,NULL,pthreadFunc,(void *)c);
}
//发送字符串

int conmmandCheck(char *c)
{
    char tmp[6] = {0};
    char *command[] = {"rm","mv","cd","mkdir","ls","pwd","gets","puts"};  
    int cmp;
    int i;
    for(i = 0; c[i] != '\0' && c[i] != '\n' && c[i] != ' ' && i < 6;i++)
    {
        tmp[i] = c[i];
    }
    tmp[i] = '\0';
    //printf("tmp = %s\n",tmp);
    for(i = 0;i <= PUTS;i++)
    {
        //printf("command = %s\n",command[i]);
        cmp = strcmp(tmp,command[i]);
        if(!cmp)
        {
            return i;
        }
    }
    return -1;
}

int main(int argc,char *argv[3])
{
    ARGS_CHECK(argc,3);
    int mfd;
    int ret;
    tmpInformationInit();
    //------------------------------------------------------初始界面
    do{
        menu();//输入用户名密码
        clientInit(&mfd,argv[1],argv[2]);//连接服务器
        ret = sendInfor(mfd);//发送验证信息
    }while(ret);
    //sendCommand(mfd,char *p);
    //------------------------------------------------------
    //连接服务器
    //给子线程也注册一个连接

    //用epoll监控gfd,和标准输入
    int epfd = epoll_create(1);
    struct epoll_event event;
    struct epoll_event *evs;

    event.data.fd = mfd;
    event.events = EPOLLIN;
    epoll_ctl(epfd,EPOLL_CTL_ADD,mfd,&event);


    event.data.fd = STDIN_FILENO;
    event.events = EPOLLIN;
    epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);

    command_t ins;
    int readyNum;
    int i;
    int fdNum = 2;
    evs = (struct epoll_event*)calloc(fdNum,sizeof(int));
    
    int len;
    char buf[4096];
    char *isTrue = "Error";
    char savPath[128];
    while(1)
    {
        readyNum = epoll_wait(epfd,evs,fdNum,-1);
        for(i = 0;i < readyNum;i++)
        {
            if(mfd == evs[i].data.fd)
            {
                memset(buf,0,sizeof(buf));
                recvData(mfd,(char *)&len,sizeof(int));
                recvData(mfd,buf,len);
                system("clear");
                printf("%s\n",buf);
                if(!strncmp(buf,isTrue,5))
                {
                    memset(tmpInf.curPath,0,sizeof(tmpInf.curPath));
                    strcpy(tmpInf.curPath,savPath);
                }
                //recvFile
            }else{ 
                if(STDIN_FILENO == evs[i].data.fd)
                {
                    //1.输入命令
                    memset(&ins,0,sizeof(ins));
                    read(STDIN_FILENO,ins.instruct,sizeof(ins.instruct));
                    //2.判断合法性及类型 1类型gets,2类型其他
                    ins.type = conmmandCheck(ins.instruct);
                    if(-1 == ins.type)
                    {
                        printf("Error command\n");
                    }else{
                        if(ins.type <= PWD)
                        {
                            //若1类型，交给mfd请求(主线程)
                            memset(savPath,0,sizeof(savPath));
                            strcpy(savPath,tmpInf.curPath);
                            ret = sendCommand(mfd,ins);
                            /*if(-1 == ret)
                              {
                            //若连接断开了，则重连，重新注册epoll
                            close(mfd);
                            clientInit(&mfd,argv[1],argv[2]);
                            event.data.fd = mfd;
                            event.events = EPOLLIN;
                            epoll_ctl(epfd,EPOLL_CTL_ADD,mfd,&event);
                            sendInfor(mfd);
                            sendCommand(mfd,ins);
                            }*/
                        }else{
                            //若2类型，交给gfd请求(子线程)
                            //创建子线程
                            complexCommand_t cmpCmd;
                            memset(&cmpCmd,0,sizeof(cmpCmd));
                            cmpCmd.ins = ins;
                            strcpy(cmpCmd.addr,argv[1]);
                            strcpy(cmpCmd.port,argv[2]);
                            printf("type = %d,instruct: %s",cmpCmd.ins.type,cmpCmd.ins.instruct);
                            pthreadInit(&cmpCmd);

                            /*--------------------------------------------------------    
                            //给子线程cfd注册监控
                            event.data.fd = cfd;
                            event.events = EPOLLIN;
                            epoll_ctl(epfd,EPOLL_CTL_ADD,cfd,&event);
                            fdNum++;
                            evs = (struct epoll_event*)calloc(fdNum,sizeof(int));
                            pNode pNew = (pNode)calloc(1,sizeof(Node));
                            pNew->command.type = ret;
                            strcpy(pNew->command.intstruct,command);
                            commandQueuePush(&cht.commandQueue,pNew);
                            //pthread_cond_signal(&cht.cond);
                            //printf("other command\n");
                            -----------------------------------------------------------*/
                        }
                    }
                }
            }
            }
        }
    }
