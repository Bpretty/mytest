#include <stdio.h>
#include "tree.h"

//前序遍历
void preorder( pNode p )
{
    if( p == NULL ) return;
    printf("%d\n", p->data);

    preorder( p->pL );
    preorder( p->pR );
}

// 中序遍历
void midorder( pNode p )
{
    if( p == NULL ) return;

    preorder( p->pL );
    printf("%d\n", p->data);
    preorder( p->pR );
}

// 后序遍历
void postorder( pNode p )
{
    if( p == NULL ) return;

    preorder( p->pL );
    preorder( p->pR );
    printf("%d\n", p->data);
}

void f1()
{
    pNode p = InitTree(); 

    preorder( p );
}

int main()
{
    f1();

    return 0;
}

