#include "stdio.h"
#include "stdlib.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: BST  
// Jon's BST/BT
// Look up (Non-recursive)
// Find number by Binary Search Tree for Array
// 


int	findNumFrSortedNumArray(int* arrayInput, int arrayLen, int Val)
{
	int start = 0;
	int end = arrayLen;
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
		else if(arrayInput[mid] < Val)
		{
			start = mid + 1;
		}
		else
		{
			end = mid - 1;
		}
		
	}
}

int main()
{
	// Quiz 1. find number from sorted number array.
	//                  0  1  2  3  4   5   6   7   8  
	int arrayInput[] = {1, 3, 5, 7, 9, 13, 25, 27, 35};
	int lenGth = sizeof(arrayInput)/sizeof(int);

	int findVal = 13;
	int inDex;
	inDex = findNumFrSortedNumArray(arrayInput, lenGth, findVal);
	printf("inDex = %d\n", inDex);
}
#endif