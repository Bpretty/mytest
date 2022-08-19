#include "tree.h"
#include <iostream>

// 非递归遍历实现均为伪代码

// 非递归前序遍历 
void Preorder( pNode p )
{
    Stack stack;  // 
    stack.push( p );

    while( !stack.IsEmpty() )
    {
        pNode p = stack.pop();
        printf("%d\n",p->data);

        if (p->pR) stack.push( p->pR );

        if (p->pL) stack.push( p->pL );
    }
}


pNode GetNode( pNode p, Stack* s )
{
    if (p == NULL ) return NULL;

    while( p->pL )
    {
        s->push( p );
        p = p->pL;
    }

    return p;
}

void Midorder( pNode p )
{
    if (p== NULL) return;

    Stack* s;
    pNode t = GetNode( p, s);

    while( t )
    {
        printf(" %d \n", t->data);

        if(p->pR){
            GetNode( p->pR, s );
        }else if(!s.IsEmpty()){
            t = s.pop();
        }else{
            break;
        }
    }
}

/*
 * TODO 后续再看
pNode GetNode( pNode p, Stack* stack  )
{
    pNode pRst = p;

    stack.push( p );

    while( p->pL )
    {
        stack.push( p->pL );
        p = p->pL;
    }

    return pRst;
}

// 非递归中序遍历
void Midorder( pNode* p )
{
    if ( p == NULL ) return;

    Stack stack;
    GetNode( p, &stack );
    while( !stack.IsEmpty() )
    {
        pNode e = stack.pop();
        printf("%d\n", e->data);

        if (p->pR)  GetNode( p->pR, &stack );
        
    }
}

*/

// 非递归后续遍历 TODO

int main()
{
    return 0;
}

