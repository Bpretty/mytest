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
#define READ_DATA_SIZE  1024
#define MD5_SIZE        16
#define MD5_STR_LEN     (MD5_SIZE * 2)
#define ARGS_CHECK(argc,val) {if(argc!=val) {printf("error args\n");return -1;}}
#define	ERROR_CHECK(ret,retval,funcname) {if(retval==ret){perror(funcname);return -1;}} 
#define PTHREAD_RET_CHECK(ret,funcname) {if(ret != 0) { printf("%s failed\n",funcname);return ret; }}
#define SWAP(a,b) {int tmp = a; a = b; b = tmp;}
#define FILENAME "file"
#define SALTLEN 10
//传输数据结构体(小火车)
typedef struct{
    int dataLen;//车厢长度
    char buf[1000];//车厢
}train;

typedef struct{
    int flag;
    char username[30];
    char token[100];
    char curPath[256];
    char passwd[30];
}tmpInformation,*pTmpInf;

tmpInformation tmpInf;

void tmpInformationInit();
int tcpServerInit(int *,char *,char *);

int sendData(int newFd,char *p,int size);
int recvData(int newFd,char *p,int size);
int recvFile(int sfd,char *filename,long filesize);
char * saltGenerate();

void logInfunc();
void exitFunc();
void registerFunc();
void menu();


int Compute_file_md5(const char *file_path, char *md5_str);
#endif
