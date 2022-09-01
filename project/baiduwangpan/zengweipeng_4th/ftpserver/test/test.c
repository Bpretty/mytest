#include <stdio.h>
#include <Myhead.h>
#include <mysql/mysql.h>
#define DEFAULTPATH "../../../../Downloads/privateSpace/"
int IsNuLLInSQL(char *querySql);
int DeleteSQL(char *querySql);
int queryMaxCode(int uId);
int getMd5SQL(char *querySql,char *md5);
int getAllMd5SQL(char *querySql,char (*)[33],int precode,int uId);
int getDirNum(int uId,int precode,int *dirArry);
int REMOVE_By_MD5(char *md5,int precode,int uId);
int IsNuLLInSQLC(char *querySql);
int dirNameSQL(char *querySql,char *name);

void InitTime(int tv_sec,int tv_usec);
int main()
{
    InitTime(1,0);
    while(1)
    {
        sleep(5);
    };
    return 0;
}
void sighandle(int sig)
{
    //指针加一
    printf("hi\n");
}
void InitTime(int tv_sec,int tv_usec)
{
    signal(SIGALRM,sighandle);
    alarm(0);
    struct itimerval tm;
    tm.it_value.tv_sec=tv_sec;
    tm.it_value.tv_usec=tv_usec;
    tm.it_interval.tv_sec=tv_sec;
    tm.it_interval.tv_usec=tv_usec;
    if(-1==setitimer(ITIMER_REAL,&tm,NULL))
    {
        perror("setitimer");
        exit(-1);
    };
}
int REMOVE_By_MD5(char *md5,int precode,int uId)
{
    char querySql[100]={0};
    int ret=IsNuLLInSQL(querySql);
    char path[120]={0};
    //查询链接数量
    memset(querySql,0,sizeof(querySql));
    sprintf(querySql,"%s%s%s","select count(md5) from file where md5='",md5,"'");
    sprintf(path,"%s%s",DEFAULTPATH,md5);
    ret=IsNuLLInSQL(querySql);
    if(ret==1)
    {
        unlink(path);
    }
    memset(querySql,0,sizeof(querySql));
    sprintf(querySql,"%s%s%s%s%d%s%d","delete from file where md5='",md5,"'"," and uId=",uId," and precode=",precode);
    DeleteSQL(querySql);
}
