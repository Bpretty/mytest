#include <stdio.h>
#include <assert.h>



char* strcpy( char* pDst,  const char* pSrc )
{

	assert( pDst!=NULL && pSrc!=NULL );

	char* p = pDst;

	while( *p++ = *pSrc++ );

	return pDst;
}

int main()
{

	char s[6]= {0};
	strcpy( s, "hello" );

	printf( "%s\n", s );

	return 0;
}
