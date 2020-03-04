#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "limits.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: static variable, static function, macro
// static, 
// 

void foo()
{
    static int fi = 8888;
    for(int a=0; a<10; a++)
    {
        static int fi = 0;
        fi++;
        printf("fi : %d\n", fi);
    }
    printf("Fi : %d\n", fi);
}

#define MAX(a, b) { (a > b) ? a : b;}

int main(void)
{
    foo();
    foo();

    int a, b;
    a = 3; b = 4;
    //(a>b)?a:b
    //printf("max macro : %d \n", MAX(3,4));

    return 0;
}

#endif