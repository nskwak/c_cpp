#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#if 1
///////////////////////////////////////////////////////////////////////////////////
// function: find missed value in array during copying
// int arrN[] = {1,2,10,12,3,4,10,12,6,7};
// int copiedArrayNmissed1[] = {1,12,4,10,3,10,2,12,7};     -> 6
// int copiedArrayNmissed2[] = {1,12,4,10,3,10,12,7};       -> answer is 2, 6 but result is 1, 7
// char arrC[] = {'a','p','r','u','o','t','c','e','w','z'};
// char copiedArrayCmissed1[] = {'a','t','c','e','p','u','o','w','z'};  -> r
// char copiedArrayCmissed2[] = {'a','r','u','p','z','t','e','w'};      -> c, o

int ArraySum(int* dataIn, int size)
{
    int sum = 0;
    for(int i=0; i<size; i++)
    {
        sum += dataIn[i];
    }
    return sum;
}

int ArrayChSum(char* dataIn, int size)
{
    int sum = 0;
    for(int i=0; i<size; i++)
    {
        sum += (int)dataIn[i];
    }
    return sum;
}

int main()
{
    int arrN[] = {1,2,10,12,3,4,10,12,6,7};
    int copiedArrayNmissed1[] = {1,12,4,10,3,10,2,12,7};
    int copiedArrayNmissed2[] = {1,12,4,10,3,10,12,7};
    int lenGtharrN = sizeof(arrN)/sizeof(int);
    int lenGthcopiedArrayNmissed1 = sizeof(copiedArrayNmissed1)/sizeof(int);
    int lenGthcopiedArrayNmissed2 = sizeof(copiedArrayNmissed2)/sizeof(int);
    char arrC[] = {'a','p','r','u','o','t','c','e','w','z'};
    char copiedArrayCmissed1[] = {'a','t','c','e','p','u','o','w','z'};
    char copiedArrayCmissed2[] = {'a','r','u','p','z','t','e','w'};
    int lenGtharrC = sizeof(arrC)/sizeof(char);
    int lenGthcopiedArrayCmissed1 = sizeof(copiedArrayCmissed1)/sizeof(char);
    int lenGthcopiedArrayCmissed2 = sizeof(copiedArrayCmissed2)/sizeof(char);
    int loopcnt = 0;

    int sumarrN = 0; int sumMissed1 = 0; int sumMissed2 = 0;
    sumarrN = ArraySum(arrN, lenGtharrN);
    sumMissed1 = ArraySum(copiedArrayNmissed1, lenGthcopiedArrayNmissed1);
    sumMissed2 = ArraySum(copiedArrayNmissed2, lenGthcopiedArrayNmissed2);
    //printf("%d %d %d\n", sumarrN, sumMissed1, sumMissed2);

    printf("====================================================\n");
    printf("1. one not copied value is %d \n", (sumarrN-sumMissed1));

    printf("====================================================\n");
    int twosum = sumarrN - sumMissed2;
    printf("twosum: %d \n", twosum);
    for(int i=0; i<lenGtharrN; i++)
    {
        for(int jj=i+1; jj<lenGtharrN; jj++)
        {
            if(arrN[jj] < arrN[i])
            {
                int tmp = arrN[i];
                arrN[i] = arrN[jj];
                arrN[jj] = tmp;
            }
        }
    }
    int m = lenGtharrN / 2;
    int start = 0;
    int end = lenGtharrN;
    while(start < end)
    {
        if((arrN[start]+arrN[end]) == twosum)
        {
            break;
        }
        else if((arrN[start]+arrN[end]) > twosum)
        {
            end -= 1;
        }
        else
            start += 1;
    }
    printf("2. two not copied value is %d, %d\n", arrN[start], arrN[end]);
    printf("Total loop count = %d\n", loopcnt);

    printf("====================================================\n");
    //printf("%d \n", (int)arrC[0]);
    sumarrN = ArrayChSum(arrC, lenGtharrC);
    sumMissed1 = ArrayChSum(copiedArrayCmissed1, lenGthcopiedArrayCmissed1);
    sumMissed2 = ArrayChSum(copiedArrayCmissed2, lenGthcopiedArrayCmissed2);
    //printf("%d %d %d\n", sumarrN, sumMissed1, sumMissed2);
    printf("====================================================\n");
    printf("3. one not copied value is %c \n", (sumarrN-sumMissed1));

    printf("====================================================\n");
    twosum = sumarrN - sumMissed2;
    //printf("twosum: %d \n", twosum);
    for(int i=0; i<lenGtharrC; i++)
    {
        for(int jj=i+1; jj<lenGtharrC; jj++)
        {
            if((int)arrC[jj] < (int)arrC[i])
            {
                char tmp = arrC[i];
                arrC[i] = arrC[jj];
                arrC[jj] = tmp;
            }
        }
    }
    /*
    for(int i=0; i<lenGtharrC; i++)
    {
        printf("%c ", arrC[i]);
    }
    printf("\n");
    */
    start = 0;
    end = lenGtharrC-1;
    while(start < end)
    {
        //printf("%c   %c \n", arrC[start], arrC[end]);
        if(((int)arrC[start]+(int)arrC[end]) == twosum)
        {
            break;
        }
        else if(((int)arrC[start]+(int)arrC[end]) > twosum)
        {
            end -= 1;
        }
        else
            start += 1;
    }
    printf("4. not copied two values are %c, %c\n", arrC[start], arrC[end]);
    //printf("Total loop count = %d\n", loopcnt);

    return 0;
}
#endif
