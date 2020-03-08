#if 1
#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

///////////////////////////////////////////////////////////////////////////////////
// function: LeetCode:Easy 509. Fibonacci Number, recursion, recursive calling
#include <stdio.h>
#include <malloc.h>

int fibonacci (int number)
{
    int val;
    if (number == 0)
        return 0;
    else if(number == 1)
        return 1;
    else
    {
        val = fibonacci(number - 1) + fibonacci(number - 2);
    }
}

int main()
{
    int result, num = 7;
    result = fibonacci(num);
    printf("fibonacci of %d is %d\n", num, result);
}

#endif