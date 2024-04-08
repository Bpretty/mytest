#include <iostream>

struct ListNode
{
    int value;
    struct ListNode *next;
};

ListNode* ReverseList(ListNode* pHead) 
{
    ListNode* pCur=pHead->next;
    if(!pCur) return pHead;

    ListNode* pNext = pCur->next;
    ListNode* pBefore = NULL;
    while(!pNext)
    {
        pCur->next = pBefore;
        pNext->next = pCur;

        pBefore = pCur;
        pCur = pNext;
        pNext = pNext->next;
    }

    pHead->next = pCur;
    return pHead;
}

void test0()
{
    int a[] = {1,2,3};

    ListNode* pHead = nullptr;
    ListNode* pCur = pHead;
    for(int i = 0; i < 3; i++)
    {
        ListNode *pNode = new ListNode;
        pNode->value = a[i];

        pCur->next = pNode;
    }
}

int main()
{
    test0();
    
    return 0;
}

