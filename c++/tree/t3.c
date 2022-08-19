#include <stdio.h>
#include "tree.h"

// 求二叉树中节点的最大距离
MyResult GetMaxDistance( pNode p )
{
    if( p == NULL )
    {
        MyResult Empty = {0, -1};
        return Empty;
    }

    MyResult left,right,rst;

    left = GetMaxDistance( p->pL );
    right = GetMaxDistance( p->pR );
    rst.maxDepth = Max( left.maxDepth + 1, right.maxDepth + 1 );

    rst.maxDistance = Max( Max( left.maxDistance, right.maxDistance ), \
                                left.maxDepth + right.maxDepth + 2 );

    return rst;
}

void f1()
{
    pNode p = InitTree(); 

    MyResult rst = GetMaxDistance( p );
    printf( "树的最大距离为 %d\n", rst.maxDistance );
}

int main()
{
    f1();

    return 0;
}

