#include "stdio.h"
#include "stdlib.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: BST  
// Jon's BST/BT
// Look up (Non-recursive)
// Find number by Binary Search Tree for Array which is unsorted due to shift.
// 
int	findNumFrShiftedNumArray(int* arrayInput, int arrayLen, int Val)
{
	int start = 0;
	int end = arrayLen - 1;
	int mid;
	while(start <= end)
	{
		printf("A ");
		mid = (start+end)/2;
		if(arrayInput[mid] == Val)
		{
			printf("find arrayInput[%d] = %d\n", mid, Val);
			return mid;
		}
		else if(arrayInput[start] <= arrayInput[mid])
		{
			printf(" arrayInput[mid] = %d\n", arrayInput[mid]);
			if(Val > arrayInput[mid])
				start = mid + 1;
			else if(Val >= arrayInput[start])
				end = mid - 1;
			else
				start = mid + 1;
		}
		else if (Val < arrayInput[mid])
			end = mid - 1;
		else if (Val <= arrayInput[end])
			start = mid + 1;
		else
			start = mid + start;		
	}
	return -1;
}

int main()
{
	// Quiz 1. find number from sorted number array.
	//                   0  1  2  3  4  5   6   7   8  
	int arrayInput[] = {13, 25, 27, 35, 1, 3, 5, 7, 9};
	//int arrayInput[] = {25, 1, 3, 4, 5, 7, 10, 14, 15, 16, 19, 20};
	int lenGth = sizeof(arrayInput)/sizeof(int);

	int findVal = 5;
	int inDex;
	inDex = findNumFrShiftedNumArray(arrayInput, lenGth, findVal);
	printf("inDex = %d\n", inDex);

	int tmp;
	for(int i=0; i<lenGth; i++)
	{
		for(int j=0; j<i; j++)
		{
			printf("B ");
			if(arrayInput[j]>arrayInput[i])
			{
				tmp = arrayInput[j];
				arrayInput[j] = arrayInput[i];
				arrayInput[i] = tmp;
			}
		}
	}

	for(int i=0; i<lenGth; i++)
	{
		printf("%d ", arrayInput[i]);
	}
	printf("\n");

	for(int i=0; i<lenGth; i++)
	{
		printf("C ");
		if(findVal == arrayInput[i])
		{
			printf("found Val = arrayInput[%d] = %d\n", i, arrayInput[i]);
			break;
		}
	}
	return 0;
}
#endif