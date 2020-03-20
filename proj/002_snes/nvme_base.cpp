#include <iostream>
#include <cstdlib>			//srand
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#include "nvme_base.h"

using namespace std; 
//using namespace mirne::SCF::NVME;

nvme_base_c::nvme_base_c( char* argv[] )
{
	int m_device = 0;
    cout << "nvme_base_c::nvme_base_c" << endl;

	for (int i=1; argv[i]; i++) {
		if (strcmp(argv[i],"-dev")==0 && argv[i+1]) {
			m_device = atoi(argv[i+1]);
		}
	}
	scf_init() ;
}

void nvme_base_c::Start( int mode )
{
	cout << "nvme_base_c::Start :" << mode << endl;
	/*
	pthread_attr_t attr ;
	pthread_attr_init( &attr ) ;
	pthread_create( &m_thread_main, &attr, nvme_main_routine, (void*)this ) ;
	pthread_setaffinity_np( m_thread_main, sizeof(cpuset), &cpuset ) ;

	//IdentifyController() ;
	//openCloseNandAccess( 0 )
	//OpenDrive() ;
	*/
}

void nvme_base_c::scf_init( void )
{
    cout << "nvme_base_c::scf_init" << endl;
	time_t timer ;
	time(&timer) ;
	srand( timer ) ; 
}

void nvme_base_c::scf_close( void )
{
    cout << "nvme_base_c::scf_close" << endl;
	return ;
}

