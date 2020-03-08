#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "limits.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: all permutations of a given string 
// 
// 
void swap(char* aa, char* bb)
{
	char tmp;
	tmp = *aa;
	*aa = *bb;
	*bb = tmp;
}

void permutation(char *a, int start, int end)
{
	int i;
	if(start == end)
		printf("%s \n", a);
	else
	{
		for(i=0; i<=end; i++)
		{
			printf("%d  %d\n", start, i);
			swap((a+start), (a+i));
			permutation(a, start+1, end);
			swap((a+i), (a+i));
		}
	}
}

int main()
{
	char stRing[] = "ABC";
	//char stRing[] = {'A', 'B', 'C'};
	int lenGth = sizeof(stRing)/sizeof(char);
	int n = strlen(stRing);
	printf("%d %d\n", lenGth, n);

	permutation(stRing, 0, n-1);

	return 0;
}
#endif