#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "limits.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: merge two sorted array
// input : a = {1, 3, 4, 6, 8, 12, 86}, b = {5, 10}
// output : {1, 3, 4, 5, 6, 8, 10, 12, 86}
int main()
{
	int arrA[] = {1, 3, 4, 6, 8, 12, 86};
	int arrB[] = {5, 10};
	char arrC[] = {'a', 'b', 'c'};
	char arrD[] = "abc";
	int result[256] = {};

	int lenGthA = sizeof(arrA)/sizeof(int) - 1;
	int lenGthB = sizeof(arrB)/sizeof(int) - 1;
	int lenGthT = lenGthA + lenGthB + 1;
	int lll = strlen(arrC);
	int mmm = strlen(arrD);

	printf("display array length: %d, %d, %d, %d, %d\n", lenGthA, lenGthB, lenGthT, lll, mmm);
	for(int i=0; i<=lenGthT; i++)
	{
		if(i <= lenGthA)
		{
			result[i] = arrA[i];
		}
		else
		{
			result[i] = 0;
		}
	}
	for(int i=0; i <= lenGthT; i++)
	{
		printf("%d ", result[i]);
	}
	printf("\n");

	while((lenGthA >= 0) && (lenGthB >= 0))
	{
		printf("1. arrA[%d]: %d, arrB[%d]: %d, result[%d]: %d\n", lenGthA, arrA[lenGthA], lenGthB, arrB[lenGthB], lenGthT, result[lenGthT]);
		if(arrA[lenGthA] > arrB[lenGthB])
		{
			printf("2. %d, %d\n", arrA[lenGthA], arrB[lenGthB]);
			result[lenGthT] = arrA[lenGthA];
			lenGthA -= 1;
			lenGthT -= 1;
		}
		else
		{
			printf("3. %d, %d\n", arrA[lenGthA], arrB[lenGthB]);
			result[lenGthT] = arrB[lenGthB];
			lenGthB -= 1;
			lenGthT -= 1;
		}
	}
	printf("\n");
	printf("\n");
	for(int i=0; i <= 8; i++)
	{
		printf("%d ", result[i]);
	}
	printf("\n");

	return 0;
}
#endif
