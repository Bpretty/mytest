#include "commandQueue.h"

void commandQueueInit(pCommandQueue pwq,int capacity)
{
    memset(pwq,0,sizeof(commandQueue_t));
    pwq->capacity = capacity;
    pwq->queueSize = 0;
    pwq->head = NULL;
    pwq->tail = NULL;
    pthread_mutex_init(&pwq->lock,NULL);
}
int commandQueuePush(pCommandQueue pwq,pNode node)
{
    if(pwq->queueSize == pwq->capacity)
    {
        printf("the queue is full %d\n",pwq->queueSize);
        return -1;
    }
    if(NULL == pwq->head)
    {
        pwq->head = node;
        pwq->tail = node;
    }else{
        pwq->tail->next = node;
        pwq->tail = node;
    }
    pwq->queueSize++;
    return 0;
}
int commandQueuePop(pCommandQueue pwq,pNode *node)
{
    if(0 == pwq->queueSize)
    {
        printf("the queue is empty\n");
        return -1;
    }
    node = &pwq->head;
    pwq->head = pwq->head->next;
    if(NULL == pwq->head)
    {
        pwq->tail = NULL;
    }
    pwq->queueSize--;
    return 0;
}

