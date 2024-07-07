#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int main()
{
	int n;
	scanf("%d",&n);
	int i = 1, total = 1;
	while (i <= n)
	{
		total = total * i;
		i++;
	}
	printf("%d\n", total);
	return 0;
}
