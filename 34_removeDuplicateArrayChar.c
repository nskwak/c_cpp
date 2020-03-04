#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "limits.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: delete duplicate with hash table
// 
// 
int main()
{
	//char str[] = {'a', 'b', 'c', 'a', 'e', 'b', 'g', 'a', 'b', 'd'};
	char str[] = "abcaebgabd";
	int i;
	char arr[256] = {};
	char result[256] = {};
	int k = 0;

	for(i = 0; str[i]; i++)
	{
		printf("%c ", str[i]);
		arr[str[i]]++;
		if(arr[str[i]] == 1)
		{
			result[k++] = str[i];
		}
	}
	printf("\n");

	for(i = 0; i < k;i++)
	{
		printf("%c ", result[i]);
	}
	return 0;
}
#endif
