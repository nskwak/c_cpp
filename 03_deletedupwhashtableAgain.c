#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

///////////////////////////////////////////////////////////////////////////////////
// Try again with James
// function: delete duplicate with hash table
// {'a', 'b', 'c', 'a', 'e', 'b', 'g', 'a', 'b', 'd'};

int main()
{
    //char str[] = {'a', 'b', 'c', 'a', 'e', 'b', 'g', 'a', 'b', 'd'};
    char str[] = {"bcabcefg"};

    int ii, jj, kk, lenGth;
    char tmp[256] = {};
    char rst[256] = {};
    kk = 0;

    lenGth = sizeof(str)/sizeof(char);
    printf("length = %d\n", lenGth);
    for(int i=0; i<lenGth; i++)
    {
        tmp[str[i]]++;
        printf("%c %d \n", str[i], tmp[str[i]]);
        if(tmp[str[i]] == 1)
        {
            rst[kk] = str[i];
            kk++;
        }
    }
    printf("=========================================\n");
    for(ii=0; ii<kk; ii++)
    {
        printf("%c ", rst[ii]);
    }
    printf("\n");

    return 0;
}