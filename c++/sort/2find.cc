// 二分查找实现

#include <stdio.h>
#include <iostream>

using namespace std;

int find( int  a[], int b , int c)
{
	int low = 0, high = b - 1;
	int mid = 0;
	
	while( low <= high )
	{
		mid = low + ( high - low ) / 2;
		
		if( a[mid] == c )
			return mid;

		if(a[mid] > c )
		{
			high = mid - 1;
		}else{
			low = mid + 1;
		}
	}

	return -1;

}


int main()
{
	int b[] = { 1,2,3,4,5  };
	int a = find( b, 5, 10  );

	printf( "找到的值为:%d\n", a  );
}

