#ifndef __FACTORY_H__
#define __FACTORY_H__
#include"head.h"
#include"workQueue.h"
#define MAXFDNUM 1000
//#include"transmitFile.h"
typedef struct{
    int pthreadNum;
    pthread_t *pthid;
    pthread_cond_t cond;
    workQueue_t workQueue;
    int waitNum;
    int startFlag;
    int endFlag;
}factory_t,*pFactory;

MYSQL *conn;
factory_t factory;
factory_t qFactory;

void factoryInit(pFactory pf,int pthreadNum,int capacity);
void factoryStart(pFactory pf,int flag);
void factoryEnd(pFactory pf);
void factoryClose(int signum,siginfo_t *p,void *p2);
void *transmitFile(void *p);
void *exitThread(void *p);
#endif
