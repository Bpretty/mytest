#include <stdio.h>

#include <iostream>

using namespace std;

//此题内存重叠问题的处理,大部分简单使用pSrc<pDst时从尾部开始复制元素
//其实还情况还可以细分,细分的话要看下数据长度,猜测是为了减少条件判断很多答案使用pSrc<pDst
//另外,面试官还可以通过此题目考察内存对齐知识(属于高阶了)

void* myMemcpy( void * pDst, void* pSrc, size_t nSize )
{
	char* Dst = pDst, Src = pSrc;

	if(Src > Dst)
	{
		while( nSize-- )
		{
			*Dst++ = *Src++;
		}
	}else
	{
		Dst = Dst + nSize -1;
		Src = Src + nSize -1;

		while( nSize -- )
		{
			*Dst-- = *Src--
		}
	}

	return pDst;
}

