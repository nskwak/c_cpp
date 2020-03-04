#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "limits.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: swap array 
// 
// 

int main()
{
	char arrayA[] = {'a', 'b', 'c', 'd', 'e'};
	int lenGth = sizeof(arrayA)/sizeof(char);
	char i, tmp;

	for(i=0;i<lenGth;i++)
		printf("%c ", arrayA[i]);
	printf("\n");

	for(int i = 0; i<(lenGth/2); i++)
	{
		tmp = arrayA[i];
		arrayA[i] = arrayA[lenGth-1-i];
		arrayA[lenGth-1-i] = tmp;
	}

	for(i=0;i<lenGth;i++)
		printf("%c ", arrayA[i]);
	printf("\n");

	return 0;
}
#endif