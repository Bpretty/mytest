#include <stdio.h>

void sort(int A[], int n)
{
    for(int i = 1; i < n; i++)
    {
        int left = 0, right = i-1;
        int tmp = A[i];

        int middle = 0;
        while(left < right)
        {
            middle = (left + right)/2;
            if(A[middle] > tmp)
            {
                right = middle - 1;
            }else if(A[middle] < tmp)
            {
                left = middle + 1;
            }else{
                break;
            }

        }

        for(int j = i - 1; j >= left; j--)
        {
            A[j+1] = A[j];
        }

        A[middle] = tmp;
    }
}

int main()
{


    return 0;
}

