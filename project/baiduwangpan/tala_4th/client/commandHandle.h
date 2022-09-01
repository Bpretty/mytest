#ifndef __COMMANDHANDLE_H__
#define __COMMANDHANDLE_H__
#include"head.h"
#include"commandQueue.h"
typedef struct{
    pthread_t *pthid;
    pthread_cond_t cond;
    commandQueue_t commandQueue;
    int exitFlag;
}commandHandleThead_t,*pCommandHandleThread;

commandHandleThead_t cht;

void threadInit();
void threadStart();
void threadEnd();
void threadClose(int signum,siginfo_t *p,void *p2);
void *threadExit(void *p);

int transmitFile(int newFd,char *filename,char *m);
#endif

