#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"
#include "string.h"
#include "malloc.h"
#include "unistd.h"
#include "math.h"
#include "time.h"
#include "signal.h"
#include "dirent.h"	
#include "stdarg.h"

#if 1   
///////////////////////////////////////////////////////////////////////////////////
// function: thread, read current time, mutex, semaphore, spinlock
// how to compile: "gcc test.c -o a.out -lpthread"
// 
void *myThreadFun(void *vargp) 
{ 
    int i = 5;
    while(1)
    {
        sleep(0.1); 
        printf("myThreadFun %d\n", i); 
        if(i-- == 0)
        {
            break;
        }
    }
    return NULL; 
} 

void *myThreadFun2(void *vargp) 
{ 
    int i = 5;
    while(1)
    {
        sleep(0.5); 
        printf("myThreadFun2 %d\n", i); 
        if(i-- == 0)
        {
            break;
        }
    }
    return NULL; 
} 

#define CLOCK_BOOTTIME 7
int main() 
{ 
    pthread_t thread_id, thread_id2, thread_id3, thread_id4; 

    time_t now = time(NULL) ;
    struct tm tm_now ;
    localtime_r(&now, &tm_now) ;
    char buff[100] ;
    strftime(buff, sizeof(buff), "%Y-%m-%d, time is %H:%M", &tm_now) ;
    printf("Time is '%s'\n", buff) ;

	struct timespec t;
    double curtime;
	int r = clock_gettime(CLOCK_BOOTTIME , &t);
    curtime = (double)(t.tv_sec) * 1000000 + t.tv_nsec / 1000;
    printf("curtime = %.0f[usec]\n", curtime);

    printf("Before Thread\n"); 
    pthread_create(&thread_id, NULL, myThreadFun, NULL); 
    pthread_create(&thread_id2, NULL, myThreadFun2, NULL); 
    pthread_join(thread_id, NULL); 
    pthread_join(thread_id2, NULL); 

    while(1)
    {
        sleep(1);
        break;
    }
    printf("After Thread\n"); 

    strftime(buff, sizeof(buff), "%Y-%m-%d, time is %H:%M", &tm_now) ;
    printf("Time is '%s'\n", buff) ;

    r = clock_gettime(CLOCK_BOOTTIME , &t);
    curtime = (double)(t.tv_sec) * 1000000 + t.tv_nsec / 1000;
    printf("curtime = %.0f[usec]\n", curtime);

    exit(0); 
}

/*
void* bf_backg(void* p)
{
	nvme_basic_c* bf_bg ;
	bf_bg= (nvme_basic_c*)p ;
	bf_bg->BackGroudBasicPerf();
	return NULL ;
}
pthread_t td;
pthread_attr_t attr ;
pthread_attr_init( &attr ) ;
printf (">< pthread_create time=[%s]\n", tstamp() );
pthread_create(&td, &attr, bf_backg, (void*)this);
pthread_join(td, NULL); 
*/
#endif
