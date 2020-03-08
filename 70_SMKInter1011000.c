#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#if 1
int foo(int* arrayIn, int len)
{

}

int main()
{
    int arrN[] = {1,0,1,1,1,0,0,1,0};
    int lenGth = sizeof(arrN)/sizeof(int);
    int count = 0;

    for(int i=0; i<lenGth; i++)
    {
        if(arrN[i] == 0)
        {
            count++;
        }
    }

    for(int i=0; i<lenGth; i++)
    {
        if(i < count)
        {
            arrN[i] = 0;
        }
        else
        {
            arrN[i] = 1;
        }
    }

    for(int i=0; i<lenGth; i++)
    {
        printf("%d ", arrN[i]);
    }

    return 0;
}
#endif
