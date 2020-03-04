#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "limits.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: remove adjacent duplicate char in array
// input : a[] = "abcddabbet"
// output : output[] = "abcdabet"
int main()
{
	char arrC[] = "abcddabbet";
	char arrT[] = {'a', 'b', 'c', 'c', 'e'};
	char prev = NULL;
	int k = 0;

	int lenGthC = strlen(arrC);

	printf("display array length: %d, arrC:%s, arrT:%s\n", lenGthC, arrC, arrT);

	for(int i=0; i<lenGthC; i++)
	{
		if(arrC[i] != prev)
		{
			arrC[k++] = arrC[i];
		}
		prev = arrC[i];
	}
	arrC[k] = NULL;
	printf("display array length: %s \n", arrC);
	return 0;
}
#endif
