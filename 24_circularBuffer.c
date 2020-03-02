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

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: circular buffer 
// https://medium.com/@charlesdobson/how-to-implement-a-simple-circular-buffer-in-c-34b7e945d30e 
// 
#define		SIZE_OF_BUFFER		    8	// Maximum size of buffer

int	circularBuffer[SIZE_OF_BUFFER] = { 0 };	// Empty circular buffer
int	optionNumber	=	0;	// User-input option number
int	readIndex	    =	0;	// Index of the read pointer
int	writeIndex	    =	0;	// Index of the write pointer
int	bufferLength	=	0;	// Number of values in circular buffer
int loopStatus      =   0;  // Loop condition variable

void enqueue(int dataIn)
{
	if(bufferLength == SIZE_OF_BUFFER) {
		printf("Queue Full! \n");
		return;
	}
	printf("enqueue: bufferLength=%d, writeIndex=%d, dataIn=%d\n", bufferLength, writeIndex, dataIn);
	circularBuffer[writeIndex] = dataIn;
	bufferLength++;
	writeIndex++;
	if(writeIndex == SIZE_OF_BUFFER) {
		writeIndex = 0;
	}
}

int dequeue()
{
	int outPut;
	if(bufferLength == 0) {
		printf("Queue Empty! \n");
		return 0;
	}
	outPut = circularBuffer[readIndex];
	printf("dequeue: bufferLength=%d, readIndex=%d, output=%d\n", bufferLength, readIndex, outPut);
	bufferLength--;
	readIndex++;
	if(readIndex == SIZE_OF_BUFFER) {
		readIndex = 0;
	}
	return outPut;
}

void printQueue()
{
	int tmp = bufferLength;
	printf("Display Queue: ");
	for(int i=0; i<tmp; i++)
	{
		printf("%d ", circularBuffer[i]);
	}
	printf("\n");
}

int main(void) 
{
	enqueue(1);	enqueue(2);	enqueue(3);	enqueue(4);	enqueue(5);
	printQueue();
	dequeue();	dequeue();	dequeue();	dequeue();
	printQueue();
	enqueue(6);	enqueue(7);	enqueue(8);	enqueue(9);	enqueue(10);
	printQueue();
	dequeue();	dequeue();	dequeue();	dequeue();	dequeue();	dequeue();	dequeue();	dequeue();	dequeue();
}

#endif
