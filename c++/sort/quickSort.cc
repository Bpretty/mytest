#include <iostream>
using namespace std;

// 快排算法

int Pos(int A[], int low, int high)
{
    int pivot = A[low];

    while( low < high )
    {
        while( low < high && A[high] >= pivot ) high--;
        A[low] = A[high];

        while( low < high && A[low] <= pivot ) low++;
        A[high] = A[low];
    }
    cout << "high = "<< high << ", low = " << low<<endl;

    A[low] = pivot;
    return low;
}

void quickSort( int A[], int low, int high )
{
    if ( low >= high ) return;

    int pos = Pos( A, low, high );
    quickSort( A, low, pos - 1 );
    quickSort( A, pos + 1, high );
}

void print( int A[], int n )
{
    for(int i = 0; i < n; i++)
    {
        cout<< A[i]<<endl;
    }
}

int main()
{
    int A[6] = { 6,5,4,3,2,1};
    quickSort( A, 0, 5 );

    print(A, 6);

    return 0;
}

