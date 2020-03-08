#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#if 1
///////////////////////////////////////////////////////////////////////////////////
// function: find min value among of 3 upto arrayN[n-1] 
// input = {1, 3, 4, 6, 7};
// copied array = {1, 3, 4, 7};
// find uncopied array value : 6

int main()
{
    int arrN[] = {1, 3, 4, 6, 7};
    int copiedArrayN[] = {1, 3, 4, 7};
    int lenGth = sizeof(arrN)/sizeof(int);
    int loopcnt = 0;

    #if 1
    for(int i=0; i<lenGth; i++)    
    {
        loopcnt++;
        if(arrN[i] == copiedArrayN[i])
        {
            printf("%d   %d\n", arrN[i], copiedArrayN[i]);
            continue;
        }
        else
        {
            printf("%d   %d\n", arrN[i], copiedArrayN[i]);
            printf("uncopied arrayN is %d\n", arrN[i]);
            break;
        }
    }
    #else
    int found = 0;
    for(int i=0; i<lenGth; i++)    
    {
        for(int j=0; j<(lenGth-1); j++)
        {
            loopcnt++;
            if(arrN[i] == copiedArrayN[j])
            {
                found = 1;
                break;
            }
        }
        if(found == 1)        found = 0;
        else
        {
            printf("uncopied arrayN is %d\n", arrN[i]);
            break;
        }
        
    }
    #endif
    printf("Total loop count = %d\n", loopcnt);

    return 0;
}
#endif
