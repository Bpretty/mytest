#ifndef __HEAD_H__
#define __HEAD_H__
#include <sys/select.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <crypt.h>
#include <mysql/mysql.h>
#include"mysqlInit.h"
#define ARGS_CHECK(argc,val) {if(argc!=val) {printf("error args\n");return -1;}}
#define	ERROR_CHECK(ret,retval,funcname) {if(retval==ret){perror(funcname);return -1;}} 
#define PTHREAD_RET_CHECK(ret,funcname) {if(ret != 0) { printf("%s failed\n",funcname);return ret; }}
#define SWAP(a,b) {int tmp = a; a = b; b = tmp;}
#define FILENAME "file"
#define SALTLEN 10
#define DEFAULT_PATH "/home/ubantu/linux_test/virtualStorage/"
#define DEFAULT_DIR "virtualStorage"
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
    PUTS
};
//传输数据结构体(小火车)
typedef struct{
    int dataLen;//车厢长度
    char buf[1000];//车厢
}train;

void tmpInformationInit();
int tcpServerInit(int *,char *,char *);

int sendData(int newFd,char *p,int size);
int recvData(int newFd,char *p,int size);

int recvFile(int socketFd,char * md5,long filesize);


void logInfunc();
void exitFunc();
void registerFunc();
void menu();

int transmitData(int newFd,char *md5,char *filename);

int verifyPassword(MYSQL *conn,const char *username,const char *ciphertext);
int verifyToken(MYSQL *conn,const char *username,const char *userToken);
char *getSalt(MYSQL *conn,const char *username);
char * saltGenerate();


void sendString(int newFd,char *str);

//命令处理
int getCode(MYSQL *conn,char *fileName,char *userName,int precode,char type);
int getCurrentCode(MYSQL *conn,char *path, char *username);
int fileCheck(MYSQL *conn,char *username,int precode,char *filename,char type);
char * lsFunc(MYSQL *conn,char *username,char *path);
int cdFunc(MYSQL *conn,char *userName,char *objPath);
int rmFunc(MYSQL *conn,int newFd,char *username,char *curPath);
int mvFunc(MYSQL *conn,int newFd,char *username,char *curPath);
int mkdirFunc(MYSQL *conn,char *userName,char *dirName,char *curPath);
int getsFunc(MYSQL *conn,int newFd,char *username,char *objPath,char *filename);
int putsFunc(MYSQL *conn,int newFd,char *username,char *objPath,char *filename,char *md5,long filesize);

#endif
