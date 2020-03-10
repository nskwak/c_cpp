#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "string.h"
#include "malloc.h"
#include "unistd.h"
#include "math.h"
#include "time.h"
#include "signal.h"
#include "dirent.h"	
#include "stdarg.h"

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

int findDiff2(int* a)
{
    int i = 0;
    int ret = 0;
    while(a[i] != '\0')
    {
        printf("%d  ", a[i]);
        if(a[i] != a[i+1])
        {
            ret = i;
            break;
        }
        i++;
    }
    return ret;
}

int findDiff3(char* a)
{
    int i = 0;
    int ret = 0;
    while(a[i] != '\0')
    {
        printf("%c  ", a[i]);
        if(a[i] != a[i+1])
        {
            ret = i;
            break;
        }
        i++;
    }
    return i;
}

int main()
{
    int arr[] = {1, 1, 1, 1, 0, 0};
    char arrC[] = {'a', 'a', 'a', 'b', 'b', 'b'};
    int inDex, arrSize;

    arrSize = sizeof(arr)/sizeof(int);
    printf("========================================\n");
    printf("=============== findDiff1 ==============\n");
    inDex = findDiff(arr, arrSize);
    printf("inDex: %d \n", inDex);
    printf("========================================\n");
    printf("=============== findDiff2 ==============\n");
    inDex = findDiff2(arr);
    printf("inDex: %d \n", inDex);

    printf("========================================\n");
    printf("=============== findDiff3 ==============\n");
    inDex = findDiff3(arrC);
    printf("inDex: %d \n", inDex);

    printf("========================================\n");
    printf("=============== check some =============\n");
    if(arr[4] == '\0')
        printf("Yes!!\n");

    return 0;
}
