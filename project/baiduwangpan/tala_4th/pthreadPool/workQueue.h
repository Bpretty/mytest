#ifndef __WORKQUEUE_H__
#define __WORKQUEUE_H__
#include"head.h"
typedef struct tagNode{
    int sockFd;
    int insType;
    struct tagNode *next;
}Node,*pNode;

typedef struct{
    pNode head;
    pNode tail;
    int capacity;
    int queueSize;
    pthread_mutex_t lock;
}workQueue_t,*pWorkQueue;

void workQueueInit(pWorkQueue wq,int capacity);//队列初始化
int  workQueuePush(pWorkQueue wq,pNode pNew);//入队
int  workQueuePop(pWorkQueue wq,pNode *node);//出队
int  isEmpty(const pWorkQueue);//判断队列是否为空

#endif
