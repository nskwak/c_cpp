#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "limits.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: find first duplicate with hash table
// 
// 
int main()
{
	//             0    1    2    3    4    5    6    7    8    9
	char str[] = {'a', 'b', 'c', 'a', 'e', 'b', 'g', 'a', 'b', 'd'};
	int i;
	char arr[256] = {};
	char result[256] = {};
	int k = 0;
	int lenGth = sizeof(str)/sizeof(char);

	//for(i = 0; str[i]; i++)
	for(i = 0; i<lenGth; i++)
	{
		printf("str[%d] = %c \n", i, str[i]);
		arr[str[i]]++;
		if(arr[str[i]] == 2)
		{
			printf("first duplicated char is %c\n", str[i]);
			k++;
			if(k == 2)
			{
				printf("second duplicated char is %c\n", str[i]);
				break;
			}
		}
	}
	return 0;
}
#endif

#if 0
int main()
{
	//            0    1    2    3    4    5    6    7    8    9
    int str[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'd'};
    int i;
    int arr[256] = {};

    for(i=0; str[i]; i++)
    {
		printf("str[%d] = %c \n", i, str[i]);
        //arr[str[i]]++;
		/*
        if(arr[str[i]] == 2)
        {
            printf("%c\n", str[i]);
            break;
        }
		*/
    }
}
#endif

