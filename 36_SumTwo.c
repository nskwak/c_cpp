#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "limits.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: two sum with BST
// input : 
// output : index
int main()
{
	////             0    1    2    3    4    5    6    7    8    9
	//char str[] = {'a', 'b', 'c', 'a', 'e', 'b', 'g', 'a', 'b', 'd'};
	//              0  1  2  3  4  5   6   7   8   9  10  11
	int arrN[]   = {2, 3, 5, 7, 8, 9, 10, 11, 14, 15, 17, 20};
	//int arrN   = {2, 14, 15, 3, 5, 10, 7, 8, 9, 11, 17, 20};

	int i;
	int target = 37;
	int start = 0;
	int lenGth = sizeof(arrN)/sizeof(int) - 1;
	while(lenGth > start)
	{
		i++;
		if((arrN[start]+arrN[lenGth]) == target)
		{
			printf("arrN[%d] + arrN[%d] = %d with loop count(%d)\n", start, lenGth, arrN[start] + arrN[lenGth], i);
			break;
		}
		else if((arrN[start]+arrN[lenGth]) > target)
			lenGth -= 1;
		else
			start += 1;		
	}

	return 0;
}
#endif
