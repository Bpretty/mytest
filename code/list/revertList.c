#include "node.h"
#include <stdlib.h>
#include <stdio.h>

// 尾插法建表
pNode createListTail()
{
    int numbers[] = {5,4,3,2,1};

    pNode pHead = (pNode)malloc(sizeof(Node));

    pNode pCur = pHead;
    for(int i = 0; i < 5; i++)
    {
        pNode pCurNode = (pNode)malloc(sizeof(Node));
        pCurNode->_value = numbers[i];

        pCur->_pNext = pCurNode;
        pCur = pCurNode;
    }
    pCur->_pNext = NULL;

    return pHead;
}

pNode createListHead()
{
    int numbers[] = {5,4,3,2,1};
    pNode pHead = (pNode)malloc(sizeof(Node));
    pHead->_pNext = NULL;

    for(int i = 0; i < 5; i++)
    {
        pNode pTmp = (pNode)malloc(sizeof(Node));
        pTmp->_value = numbers[i];

        pTmp->_pNext = pHead->_pNext;
        pHead->_pNext = pTmp;
    }

    return pHead;
}

void displayList(pNode p)
{
    if(p == NULL)
        return;

    while(p != NULL)
    {
        printf("%d \n", p->_value);
        p = p->_pNext;
    }
}

int main()
{
    //pNode p =  createListTail();
    pNode p =  createListHead();
    displayList(p->_pNext);

    return 0;
}

