#include "stdio.h"
#include "stdlib.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: Stack  
// https://www.sanfoundry.com/c-program-stack-implementation/
// Stack implementation with C
// 
// 
#define MAXSIZE 5
int s_stk[MAXSIZE] = {};
int s_top;

void push(int dataIn)
{
	if(s_top == (MAXSIZE-1))
	{
		printf("Stack is Full\n");
		return;
	}
	s_top += 1;
	s_stk[s_top] = dataIn;
}
int pop()
{
	int dataOut;
	if(s_top == -1)
	{
		printf("Stack is Empty\n");
		return (s_top);
	}
	dataOut = s_stk[s_top];
	s_top = s_top - 1;
	return dataOut;
}

void displayStack()
{
	int tmp = s_top;
	if(s_top == -1)
	{
		printf("Stack is empty\n");
		return;
	}
	while(tmp >= 0)
	{
		printf("%d ", s_stk[tmp]);
		tmp--;
	}
	printf("\n");
}
int main()
{
	s_top = -1;
	push(3);	push(63);	push(53);	push(9);	displayStack();
	push(399);	push(636);	push(5363);	displayStack();
	pop();		displayStack();
	pop();		displayStack();
}
#endif

#if 0   
///////////////////////////////////////////////////////////////////////////////////
// function: Stack  
// https://www.techiedelight.com/stack-implementation/
// Stack implementation with C
// 
// 

typedef stack
{
	int maxsize;
	int top;
	int *item;
}STACK;

#endif
