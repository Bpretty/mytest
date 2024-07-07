#include <stdio.h>
#include <iostream>
using namespace std;

int pivot(int *p, int low, int high)
{
    int value = p[low];

    while(low < high)
    {
        while(p[high] >= value && low < high)
        {
            high--;
        }
        p[low] = p[high];

        while(p[low] <= value && low < high)
        {
            low++;
        }
        p[high] = p[low];
    }

    printf("low=%d, high=%d\n", low, high);

    p[low] = value;

    return low;
}

void quickSort(int* p, int low, int high)
{
    if (low >= high)
        return;

    int pos = pivot(p, low, high);
    quickSort(p, low, pos -1);
    quickSort(p, pos+1, high);
}

int main()
{
    int numbers[] = {2,3,5,1,4};
    //int pos = pivot(numbers, 0, 4);
    //printf("找到的位置是%d, 值是 %d\n", pos, numbers[pos]);
    quickSort(numbers, 0, 4);

    for(int i = 0; i < 5; i++)
    {
        printf("%d\n", numbers[i]);
    }

    return 0;
}

