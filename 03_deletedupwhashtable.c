#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

#if 0
///////////////////////////////////////////////////////////////////////////////////
// function: delete duplicate with hash table
// {'a', 'b', 'c', 'a', 'e', 'b', 'g', 'a', 'b', 'd'};

int main()
{
    //char str[] = {'a', 'b', 'c', 'a', 'e', 'b', 'g', 'a', 'b', 'd'};
    char str[] = {"bcabc"};

    int i;
    char arr[256] = {};
    char result[256] = {};

    int lenGth = sizeof(str)/sizeof(char);

    printf("%d\n", lenGth);
    int k=0;

    for(i=0; str[i]; i++)
    {
        arr[str[i]]++;
        if(arr[str[i]] == 1)
        {
            result[k++] = str[i];
        }
    }
    for(i=0;i<k;i++)
    {
        printf("%c ", result[i]);
    }
    printf("\n");

}
#endif

///////////////////////////////////////////////////////////////////////////////////
// function: delete duplicate with hash table
// {'a', 'b', 'c', 'a', 'e', 'b', 'g', 'a', 'b', 'd'};

int main()
{
    char str[] = {'a', 'b', 'c', 'a', 'e', 'b', 'g', 'a', 'b', 'd'};
    //char str[] = {"bcabcefg"};

    int i;
    char arr[256] = {};
    char result[256] = {};

    int lenGth = sizeof(str)/sizeof(char);

    printf("%d\n", lenGth);
    int k=0;

    for(i=0; str[i]; i++)
    {
        arr[str[i]]++;
        if(arr[str[i]] == 2)
        {
            result[k++] = str[i];
            printf("%c \n", str[i]);
        }
    }

    return 0;
}
