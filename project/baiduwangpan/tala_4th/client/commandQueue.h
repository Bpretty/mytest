#ifndef __COMMANDQUEUE_H__
#define __COMMANDQUEUE_H__
#include"head.h"
typedef struct{
    int type;
    int len;
    char instruct[128];
}command_t,pCommand;

typedef struct tagNode{
    command_t command;
    struct tagNode *next;
}Node,*pNode;

typedef struct{
    pNode head;
    pNode tail;
    int capacity;
    int queueSize;
    pthread_mutex_t lock;
}commandQueue_t,*pCommandQueue;

void commandQueueInit(pCommandQueue wq,int capacity);//队列初始化
int  commandQueuePush(pCommandQueue wq,pNode pNew);//入队
int  commandQueuePop(pCommandQueue wq,pNode *node);//出队
int  isEmpty(const pCommandQueue);//判断队列是否为空

#endif
