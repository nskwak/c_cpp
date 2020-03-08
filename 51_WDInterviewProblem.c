#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "limits.h"

#if 1
int findDiff(int* a, int lenGth)
{
    printf("arr size is %d \n", lenGth);
    for(int i=0; i<lenGth; i++)
    {
        if(a[i] != a[i+1])
        {
            return i;
        }
    }
}
#endif

int main()
{
    int arr[] = {1, 1, 1, 0, 0, 0};
    int inDex, arrSize;
    #if 0   //WD indian problem
    arrSize = sizeof(arr)/sizeof(int);
    inDex = findDiff(arr, arrSize);
    printf(" %d \n", inDex);

    #else   //WD Korean problem

    int i=10;
    int* p;
    p = &i;
    printf("(p = &i) => p addr: %p - arr addr: %p\n", p, arr);
    //arr = p;
    //printf("arr = p => p addr: %p - arr addr: %p\n", p, arr);
    for(int k=0; k<6; k++)
    {
        printf("%d ", arr[k]);
    }
    printf("\n");
    printf("1. *p : %d, i : %d\n", *p, i);

    p = arr;
    printf("(p = arr) => p addr: %p - arr addr: %p\n", p, arr);
    printf("2. *p : %d, i : %d\n", *p, i);

    //arr = p;    //KK_ failed, do not use this....

    #endif

    return 0;
}
