#include <iostream>
#include <cstdlib>			//srand
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#include "unistd.h"
#include "nvme_base.h"

using namespace std; 
using namespace mirne::SCF::NVME;

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// two method to call method in class
// 1) 
// Myclass m;
// m.func1();
// 2)
// Myclass* m = new Myclass();
// m->func1();
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
volatile bool got_ctrl_c = false;
void  ctrl_c_handler( int signum )
{
	//Do not use printf/malloc and etc, there.
	//Especially linux app will crash on exit()
	printf( "Ctrl-C : signum=%d\n", signum ) ;
	got_ctrl_c = true;
}

void* nvme_main_routine(void* p)
{
	printf("[nvme_base_c-nvme_main_routine]\n");
	nvme_base_c* nvme ;
	nvme = (nvme_base_c*)p ;

	nvme->MainRoutine() ;
	printf( "Exit Main Routine\n" ) ;
	return NULL ;
}

void* nvme_admin_main_routine(void* p)
{
	printf("[nvme_base_c-nvme_admin_main_routine]\n");
	nvme_base_c* nvme ;
	nvme = (nvme_base_c*)p ;
	nvme->AdminMainRoutine() ;
	return NULL ;
}

nvme_base_c::nvme_base_c( char* argv[] )
{
	m_device = 0;
	printf("[nvme_base_c::nvme_base_c(argv)]\n");	//cout << "nvme_base_c::nvme_base_c" << endl;

	for (int i=1; argv[i]; i++) {
		if (strcmp(argv[i],"-dev")==0 && argv[i+1]) {
			m_device = atoi(argv[i+1]);
		}
	}
	printf("m_device = %d\n", m_device);
	scf_init() ;
}

void nvme_base_c::Start( int mode )
{
	printf("[nvme_base_c::Start]\n");	//cout << "nvme_base_c::Start :" << mode << endl;
	cpu_set_t cpuset ;
	pthread_attr_t attr ;
	pthread_attr_init( &attr ) ;
	pthread_create( &m_thread_main, &attr, nvme_main_routine, (void*)this ) ;
	//pthread_setaffinity_np( m_thread_main, sizeof(cpuset), &cpuset ) ;

	pthread_t thread_admin_main ;
	pthread_create( &thread_admin_main, &attr,  nvme_admin_main_routine, (void*)this ) ;
	//thread_setaffinity_np( thread_admin_main, sizeof(cpuset), &cpuset ) ;

	/*
	//IdentifyController() ;
	//openCloseNandAccess(0);
	//OpenDrive();
	//GetMetadata();
	*/
}

void nvme_base_c::scf_init( void )
{
	printf("[nvme_base_c::scf_init]\n");	//cout << "nvme_base_c::scf_init" << endl;
	time_t timer ;
	time(&timer) ;
	srand( timer ) ; 

	//openDevice(m_device);
	//global variable setup
}

void nvme_base_c::scf_close( void )
{
	printf("[nvme_base_c::scf_close]\n");	//cout << "nvme_base_c::scf_close" << endl;
	return ;
}

void* nvme_base_c::MainRoutine( void )
{
	double ts1, ts2, curtime;
	double counter;
	double next_end_phase1, next_end_phase4;;
	bool is_issued_16m;

	const double end_phase_1_interval = 9000;
	const double end_phase_4_interval = 16660;
	printf("[nvme_base_c::MainRoutine]\n");
	ts1 = getTimeAsUsec();
	next_end_phase1 = ts1 + end_phase_1_interval;
	next_end_phase4 = ts1 + end_phase_4_interval;

	printf("[nvme_base_c::MainRoutine] ts1=%.0f\n", ts1);

	while( !got_ctrl_c ) {
		ts2 = getTimeAsUsec();
		if(ts2 >= next_end_phase4)
		{
			printf("MainRoutine - 16msec \n");
			is_issued_16m = true;
		}
		if(is_issued_16m)
		{
			ts1 = getTimeAsUsec();
			printf("[nvme_base_c::MainRoutine] is_issued_16m - ts1=%.0f\n", ts1);
			//next_end_phase1 = ts1 + end_phase_1_interval;
			next_end_phase4 = ts1 + end_phase_4_interval;
			is_issued_16m = false;
		}
		usleep(10);		//per 10[usec]
	}
}

void* nvme_base_c::AdminMainRoutine( void )
{
	double ts1, ts2, curtime;
	double next_end_phase1;
	const double end_phase_1_interval = 9000;

	printf("[nvme_base_c::AdminMainRoutine]\n");
	while( !got_ctrl_c ) {
		ts1 = getTimeAsUsec();
		if((ts1) >= next_end_phase1)
		{
			printf("[nvme_base_c::AdminMainRoutine] - ts1=%.0f\n", ts1);
			next_end_phase1 = ts1 + end_phase_1_interval;
		}
		usleep(10);		//per 10[usec]
	}
}

int nvme_base_c::printf(const char *fmt, ...)
{
	va_list ap;
	int cnt;

	va_start(ap, fmt);
	cnt = vprintf(fmt, ap);
	va_end(ap);

	return cnt;
}

double nvme_base_c::getTimeAsUsec()
{
    time_t now = time(NULL) ;
    struct tm tm_now ;
    localtime_r(&now, &tm_now) ;
    char buff[100] ;
    strftime(buff, sizeof(buff), "%Y-%m-%d, time is %H:%M", &tm_now) ;
    //printf("Time is '%s'\n", buff) ;

	struct timespec t;
    double curtime;
	int r = clock_gettime(CLOCK_BOOTTIME , &t);
    curtime = (double)(t.tv_sec) * 1000000 + t.tv_nsec / 1000;
    //printf("curtime = %.0f[usec]\n", curtime);

	return curtime;
}

int nvme_base_c::LBA_Load(void)
{
	while(!got_ctrl_c)
	{
		//printf("*");
	}
}