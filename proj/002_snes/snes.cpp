#include <iostream>
#include <cstdlib>			//srand
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>
#include "snes.h"
using namespace std;
using namespace mirne::SCF::NVME;

int main(int argc, char**argv)
{
	int ret;
	int device;
	int driver_ready = false;

	printf("==========================================================\n");
	printf("[snes-main] C++ program grammer study\n");	//cout << "C++ program grammer study" << endl;

	for (int i=1; argv[i]; i++) {
		//printf("%d: %s %d\n", i, argv[i], argc);
		if (strcmp(argv[i],"-dev")==0 && argv[i+1]) {
			device = atoi(argv[i+1]);
			i++;
			continue;
		}
	}

	nvme_basic_c* nvme ; 
	nvme = new nvme_basic_c(argv) ;		//call 
	nvme->m_driver_ready = driver_ready;
	ret = nvme->Main(argc, argv); 
    return 0;
}

enum {
	CMD_StartEnd        =001,
	CMD_SplitBlock      =002,
};

int nvme_basic_c::Main( int argc, char**argv )
{
	double curtime;
	int av = 1;
	int command_id = -1;
	int param32_0;

    printf("[snes-nvme_basic_c::Main] \n"); //cout << "snes.cpp - Main " << endl;
	curtime = getTimeAsUsec();
	printf("curtime = %.0f[usec]\n", curtime);

	while(argc > av)
	{
		if ( argc>=(av+1) && strcmp( argv[av], "-q" ) == 0 ) {
			printf("argv[av] = -q\n");
			av++;
		}
		else if ( argc>=(av+2) && strcmp( argv[av], "-cl" ) == 0 ) {
			printf("argv[av] = -cl\n");
			av+=2;
		}
		else {
			break;
		}
	}
	if ( argc>=(av+1) ) {
		// SplitBlock
		if ( strcmp( argv[av], "-split" ) == 0 ) {
			command_id = CMD_SplitBlock ;
			param32_0 = atoi( argv[av+1] ) ;
		}
		// StartEnd
		else if ( strcmp( argv[av], "-0" ) == 0 ) {
			command_id = CMD_StartEnd ; 
			param32_0 = atoi( argv[av+1] ) ;
		}
	} 

	switch(command_id) {
	case CMD_StartEnd:       
		printf("CMD_StartEnd, param32_0=%d\n", param32_0); 
		Start();	// this call nvme_basic_c::Start() but nvme_base_c::Start() will be called.
		LBA_Load();
		break;
	case CMD_SplitBlock:
		printf("CMD_SplitBlock\n"); 
		break ;
	case -1: 
		break ;
	default: 
		break ;
	}
    return 0;
}

void nvme_basic_c::Start( int mode )
{
	//nvme_base_c npp; npp.Start(mode);
	nvme_base_c::Start(mode);		// call Start() of class nvme_base_c

	printf("[snes-nvme_basic_c::Start] \n");	//cout << "snes.cpp - Start " << endl;
}

void nvme_basic_c::Identify( void )
{ 
	printf("[snes-nvme_basic_c::Identify] \n");	//cout << "snes.cpp - Identify " << endl;
}
