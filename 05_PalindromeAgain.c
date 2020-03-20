#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

///////////////////////////////////////////////////////////////////////////////////
// Try-again with James
// Function: Palindrome Number
// Description : Given an integer, determines whether it reads the same way forwards as it does backwards
// Date : 03/17/2020
// input: array number, string, array char
// output: FALSE 

int main()
{
    //char str[] = {'a', 'b', 'c', 'a', 'e', 'b', 'g', 'a', 'b', 'd'};
    //char str[] = {"bcabcefg"};
    char str[] = {"bcabcefg"};
    int ii, jj, kk, lenGth;

    lenGth = sizeof(str)/sizeof(char);
    printf("length = %d\n", lenGth);

    //convert string to array char
    char *arrayC = malloc(sizeof(char)*(lenGth-1));
    int arrayCsize = sizeof(arrayC);
    printf("size of arrayC = %d\n", arrayCsize);
    for(ii=0; ii<arrayCsize; ii++)
    {
        arrayC[ii] = str[ii];
    }

    int start = 0;
    int end = arrayCsize - 1;
    while(start < end)
    {
        if(arrayC[ii] != arrayC[arrayCsize-1])
        {
            printf("not Palindrome!!\n");
            break;
        }
        else
        {
            start += 1;
            end -= 1;
        }
    }

    return 0;
}