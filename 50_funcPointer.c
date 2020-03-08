#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "limits.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: function pointer
// 

void foo(int paramA)
{
    printf("foo : %d\n", paramA);
}

void foo1(int paramA)
{
    printf("foo : %d, %d\n", paramA, paramA);
}

//int (*func)

int main()
{
    void (*fp)(int);
    fp = &foo;

    (*fp)(1);
    fp(1);

    fp = &foo1;
    (*fp)(1);
    fp(1);

	return 0;
}
#endif
