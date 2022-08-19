#include <stdio.h>
#include "tree.h"

// 求树的深度
int GetTreeDepth( pNode p )
{
    if( p == NULL ) return 0;

    int left,right;
    left = GetTreeDepth( p->pL ) + 1;
    right = GetTreeDepth( p->pR ) + 1;

    return (left > right) ? left:right;
}

void f1()
{
    pNode p = InitTree(); 

    printf( "树的深度为%d\n", GetTreeDepth( p ) );
}

int main()
{
    f1();

    return 0;
}

