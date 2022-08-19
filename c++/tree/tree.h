#include <func.h>

typedef struct Node{
    int data;
    struct Node* pL;
    struct Node* pR;
}*pNode;

// 用于二叉树节点的最大距离求取
typedef struct{
    int maxDepth;
    int maxDistance;
}MyResult;

int Max( int a, int b)
{
    return a>b ? a:b;
}

pNode GetNewNode( int n)
{
    pNode p = (pNode)malloc( sizeof(struct Node) );
    p->pL = NULL;
    p->pR = NULL;
    p->data = n;

    return p;
}

pNode InitTree()
{
    pNode pStart = GetNewNode( 1 );;
    pNode pRst = pStart;

    pStart->pL = GetNewNode( 2 );
    pStart->pR = GetNewNode( 3 );

    pStart = pStart->pL;
    pStart->pL = GetNewNode( 4 );
    pStart->pR = GetNewNode( 5 );

    pStart = pStart->pL;
    pStart->pL = GetNewNode( 6 );
    pStart->pR = GetNewNode( 7 );

    return pRst;
}


