#include "head.h"
typedef struct{
    int  precode;
    char type;
    char fileName[50];
    char userName[30];
    char md5[100];
    long fileSize;
}file_t;
int getCode(MYSQL *conn,char *fileName,char *userName,int precode,char type)
{
    char *q1 = "select code from test where filename='";
    char *q2 = "' and username='";
    char *q3 = "' and precode='";
    char *q4 = "' and type='";
    char query[255] = {0};
    int code;                                                                                                                                 
    sprintf(query,"%s%s%s%s%s%d%s%c%s",q1,fileName,q2,userName,q3,precode,q4,type,"';");
    printf("%s\n",query);
    MYSQL_RES *res = selectSql(conn,query);
    MYSQL_ROW row;
    row = mysql_fetch_row(res);
    if(NULL == row)
    {   
        mysql_free_result(res);
        return -1;
    }
    code = atoi(row[0]);
    mysql_free_result(res);
    //printf("~~~~~~~code = %d\n",code);
    return code;
}
//   /test1/test2/test3/
int getCurrentCode(MYSQL *conn,char *path, char *username)
{
    char *p = path;
    int i;
    int j = 1;
    int off[15] = {0};
    int total = 0;
    int len = strlen(p);
    char filename[20];
    int precode = 0;
    int code;
    for(i = 1;i < len;i++)
    {
        if('/' == p[i])
        {
            off[j++] = i;
            total++;
        }
    }
    if(1 == i)
    {
        return 0;
    }
    p++;
    for(i = 0;i < total;i++)
    {
        memset(filename,0,sizeof(filename));
        strncpy(filename,p,off[i+1]-off[i]-1);
        code = getCode(conn,filename,username,precode,'d');
        precode = code;
        //printf("dir %d,name :%s\n",i+1,filename);
        p+=(off[i+1]-off[i]);
    }
    printf("~~~~~~~code = %d\n",code);
    return code;
}
int fileCheck(MYSQL *conn,char *username,int precode,char *filename,char type)
{
    char *q1 = "select * from test where filename='";
    char *q2 = "' and username='";
    char *q3 = "' and precode='";
    char *q4 = "' and type='";
    char query[255] = {0};
    sprintf(query,"%s%s%s%s%s%d%s%c%s",q1,filename,q2,username,q3,precode,q4,type,"';");
    printf("%s\n",query);
    MYSQL_RES *res = selectSql(conn,query);
    MYSQL_ROW row;
    row = mysql_fetch_row(res);
    if(NULL == row)
    {   
        mysql_free_result(res);
        return 0;
    }   
    mysql_free_result(res);
    return -1;
}
char * lsFunc(MYSQL *conn,char *username,char *path)
{
    unsigned int i;
    char buf[1024] = {0};
    int precode = getCurrentCode(conn,path,username);
    char *q1 = "select  type,filename,filesize from test where username='";
    char *q2 = "' and precode='";
    char query[255] = {0};
    char white[30];
    char *p;
    memset(white,' ',sizeof(white)-1);
    white[29] = '\0';
    int lenLast;
    int lenNext;
    int count = 0;
    sprintf(query,"%s%s%s%d%s",q1,username,q2,precode,"';");
    printf("%s\n",query);
    MYSQL_RES *res = selectSql(conn,query);
    MYSQL_ROW row;
    while((row = mysql_fetch_row(res))!= NULL)                                                                                          
    {   
        count++;
        strcat(buf,row[0]);
        lenLast = strlen(row[0]);
        for(i = 1;i < mysql_num_fields(res);i++)
        {   
            lenNext = strlen(row[i]);
            strncat(buf,white,15-(lenLast + lenNext));
            strcat(buf,row[i]);
        }   
        strcat(buf,"\n");
    }   
    if(!count)
    {
        p = "Empty directory\n"; 
        printf("Empty directory\n");
    }else{
        p = buf;
    }
    mysql_free_result(res);
    return p;
}
int cdFunc(MYSQL *conn,char *userName,char *objPath)
{
    int precode = getCurrentCode(conn,objPath,userName);
    if(-1 == precode)
    {
        printf("Error path\n");
        return -1;
    }else 
        return precode;
}
int rmFunc(MYSQL *conn,int newFd,char *username,char *curPath)
{
    return 0;
}
int mvFunc(MYSQL *conn,int newFd,char *username,char *curPath)
{
    return 0;
}
int mkdirFunc(MYSQL *conn,char *userName,char *dirName,char *curPath)
{
    //首先获得当前路径下文件夹code
    int precode = getCurrentCode(conn,curPath,userName);

    int ret;
    char t = 'd';
    if(-1 == precode)
    {
        printf("Error path\n");
        return -1;
    }
    //检索该目录下是否有重名文件
    ret = fileCheck(conn,userName,precode,dirName,t);
    //ret = fileCheck(conn,precode,fileName,userName);
    if(ret)
    {
        printf("Error file have already existed\n");
        return -2;
    }else{
        //插入虚拟文件表，
        //文件夹名，用户名，文件类型，MD5(NULL)，文件大小4096
        char *q1 = "insert into test(precode,type,filename,username,filesize)values('";
        char query[200] = {0};
        sprintf(query,"%s%d%s%s%s%s%s%s%d%s",q1,precode,"','","d','",dirName,"','",userName,"','",4096,"');");
        printf("%s\n",query);
        ret = insertSql(conn,query);
    }
    return precode;
}
//int getRealFile(MYSQL *conn,)
int getsFunc(MYSQL *conn,int newFd,char *username,char *objPath,char *filename)
{
    int precode = getCurrentCode(conn,objPath,username);
    int ret;
    if(-1 == precode)
    {
        printf("Error path\n");
        return -1;
    }else{
        ret = fileCheck(conn,username,precode,filename,'f');
        if(0 == ret)
        {
            printf("No such file\n");
            return -1;
        }else{
            char md5num[40] = {0};
            char *q1 = "select md5 from test where filename='";
            char query[200] = {0};
            sprintf(query,"%s%s%s%d%s%s%s",q1,filename,"'and precode ='",precode,"' and username='",username,"';");
            printf("%s\n",query);
            MYSQL_RES *res = selectSql(conn,query);
            MYSQL_ROW row;
            row = mysql_fetch_row(res);
            strcpy(md5num,row[0]);
            transmitData(newFd,md5num,filename);
            //传输文件协议,根据对端已经接收到的resvSize进行偏移然后转发，实现续传功能
            //如果文件大于100，mmap映射发送
            return 0;
        }
    }

}
int realFileCheck(MYSQL *conn,char *md5,long filesize)
{
    char *q1 = "select *from real_file where md5='";
    char query[200] = {0};
    sprintf(query,"%s%s%s%ld%s",q1,md5,"'and filesize='",filesize,"';");
    printf("%s\n",query);
    MYSQL_RES *res = selectSql(conn,query);
    MYSQL_ROW row;
    row = mysql_fetch_row(res);
    if(NULL == row)
    {   
        mysql_free_result(res);
        return 0;
    }   
    mysql_free_result(res);
    return -1;
}
int putsFunc(MYSQL *conn,int newFd,char *username,char *objPath,char *filename,char *md5,long filesize)
{
    int precode = getCurrentCode(conn,objPath,username);
    int ret;
    if(-1 == precode)
    {
        printf("Error path\n");
        return -1;
    }else{
        //秒传，查看真实文件表里是否有该文件(md5 和 size 比对)
        ret = realFileCheck(conn,md5,filesize);
        if(0  == ret)
        {
            printf("com sfd = %d",newFd);
            ret = recvFile(newFd,md5,filesize);//接收文件
            if(!ret)
            {
                char *q1 = "insert into real_file(md5,filesize,owners)values('";
                char query[200] = {0};
                sprintf(query,"%s%s%s%ld%s%d%s",q1,md5,"','",filesize,"','",1,"');");
                printf("%s\n",query);
                ret = insertSql(conn,query);
                //增加两条记录
                char *q2 = "insert into test(precode,type,filename,username,filesize,md5)values('";
                memset(query,0,sizeof(query));
                sprintf(query,"%s%d%s%s%s%s%s%s%ld%s%s%s",q2,precode,"','","f','",filename,"','",username,"','",filesize,"','",md5,"');");
                printf("%s\n",query);
                ret = insertSql(conn,query);
            }
        }else{
            char *q2 = "insert into test(precode,type,filename,username,filesize,md5)values('";
            char query[200] = {0};
            sprintf(query,"%s%d%s%s%s%s%s%s%ld%s%s%s",q2,precode,"','","f','",filename,"','",username,"','",filesize,"','",md5,"');");
            printf("%s\n",query);
            ret = insertSql(conn,query);
        }
        //1.若有则 update 真实文件表 对应文件项userCount++
        //虚拟文件表加一条记录
        //
        //
        //2.若没有，则根据协议 接收文件
        //真实文件表添加新记录
        //虚拟文件文件表添加新纪录
    }
    return precode;
}

/*int main()
  {
//char p[50] = "ggggg";
//strcat(p,PATH);
char p2[50] = {0};
MYSQL *conn = mysqlConnInit();
strcat(p2,"/test1/test2/huyue/"); 
char *buf = lsFunc(conn,"tala",p2);
printf("%s",buf);
//int code = getCurrentCode(conn,p2,"tala");
//printf("curCode = %d\n",code);
//mkdirFunc(conn,"tala","sucTest",p2);
//char *fileName = getFileName(p2);

//printf("fileName = %s\n",fileName);
//
//
int precode = 0;
char *dirName = "test1";
char *username = "tala";
char *q1 = "insert into virtual_file_table(precode,type,filename,username,filesize)values('";
char q2[200] = {0};
sprintf(q2,"%s%d%s%s%s%s%s%s%d%s",q1,precode,"','","d','",dirName,"','",username,"','",4096,"');");
printf("%s\n",q2);
return 0;
}
*/


