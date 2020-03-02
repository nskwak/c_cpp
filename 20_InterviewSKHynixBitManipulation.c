#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "unistd.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: bit maipulation
// Cracking code page 58, 5.5
// input: 31, 14 -> output: 2

int findDupBit(int inNum)
{
    int count = 0;
    while(inNum != 0)
    {
        count++;
        printf("0x%x & 0x%x \n", inNum, (inNum-1));
        inNum &= (inNum-1);
    }
    return count;
}
int convBin(int inNum1)
{
    if(inNum1 > 1)   
        convBin(inNum1/2);
    printf("%d ", inNum1%2);
}

int main()
{
    int in1, in2, ina, rst;
    in1 = 31;
    in2 = 14;

    //rst = findDupBit(in1^in2);
    rst = findDupBit(0x7f);
    printf("findDupBit = %d\n", rst);

    #if 0
    printf("=======================================================\n");
    ina = 31;
    for(int i = 14 ; i < 50; i++)
    {
        printf("%2d:  ", i); convBin(i); printf("\n");
    }
    #endif
}
#endif

#if 0
///////////////////////////////////////////////////////////////////////////////////
// function: bit maipulation
// Cracking code page 57, 5.1
// a)  N = 1024 (10000000000),
//     M = 19 (10011),
//     i = 2, j = 6
//     Output : 1100 (1000'10011'00)
// b)  N = 1201 (10010110001)
//     M = 8 (1000)
//     i = 3, j = 6
//     Output: 1217 (1001'1000'001)

void convertDec(int invar)
{
    int a, b;

    while(invar != 0)
    {
        a = invar % 10;
        invar /= 10; 
        printf("%d ", a);
    }
    printf("\n");
}

int main()
{
    int var1, var2;
    int N, M, i, j;
    int captured_bit, cleared_bit;

    var1 = 123;
    convertDec(var1);

    //N = 1024; M = 19; i = 2; j = 6;
    N = 1201; M = 8; i = 3; j = 6;
    captured_bit = (1<<i) -1;
    cleared_bit = -1 << (j+1);
    var1 = N & captured_bit;
    N = N & cleared_bit;
    N = N | (M<<i);
    N = N | var1;

    printf("0x%x, %d \n", N, N);
}
///////////////////////////////////////////////////////////////////////////////////
#endif