#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include "limits.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: how to check Big Endian or Little Endian
// input  : 0x12345678
// output : big Endian(0x12345678) or little Endian(0x78563412)

void showMem(char* start, int n)
{
	for(int i=0; i<n; i++)
	{
        //printf("0x%.2x    ", start[i]);
        printf("0x%x    ", start[i]);
	}
    printf("\n");
}

int convertEndian(int dataIn, int n)
{
    return(((dataIn&0xFF000000)>>24) | ((dataIn&0x00FF0000)>>8) | ((dataIn&0x0000FF00)<<8) | ((dataIn&0x000000FF)<<24));
}

int main()
{
	int k = 0x12345678;
    int siZek = sizeof(int);
    int conVert;
	printf("k: 0x%x, size:%d\n", k, siZek);
    showMem((char*)&k, siZek);

    conVert = convertEndian(k, siZek);
    printf("convert Endian: 0x%x -> 0x%x\n", k, conVert);
    
	return 0;
}
#endif
