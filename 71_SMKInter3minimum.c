#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#if 1
///////////////////////////////////////////////////////////////////////////////////
// function: find min value among of 3 upto arrayN[n-1] 
// input = {1, 3, 4, 6, 3, 7, 78, 53, 2, 3};
// output = 1 3 3 3 3 7 2 2

int main()
{
    int arrN[] = {1, 3, 4, 6, 3, 7, 78, 53, 2, 3};
    int lenGth = sizeof(arrN)/sizeof(int);

    printf("lenGth = %d\n", lenGth);
    
    int* result = malloc((lenGth-2)*sizeof(int));

    for(int i=0; i<lenGth-2; i++)
    {
        result[i] = 0;
    }
    printf("1. size of result = %d\n", (int)(sizeof(result)));

    for(int i=0; i<lenGth-2; i++)
    {
        int small = 0xffff;
        for(int k=i; k<=i+2; k++)
        {
            if(arrN[k]<small)
                small = arrN[k];
        }
        result[i] = small;
    }

    for(int i=0; i<lenGth-2; i++)
    {
        printf("%d ", result[i]);
    }
    
    printf("\n2. size of result = %d\n", (int)(sizeof(result)));

    return 0;
}
#endif
