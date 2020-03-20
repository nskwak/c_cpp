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
using namespace mirne::SCF::NVME;

void nvme_base_c::Start( int mode )
{
	cout << "nvme_base_c::Start :" << mode << endl;
}

void nvme_base_c::scf_init( void )
{
	time_t timer ;
	time(&timer) ;
	srand( timer ) ; 
    cout << "nvme_base_c::scf_init" << endl;
}

void nvme_base_c::scf_close( void )
{
    cout << "nvme_base_c::scf_close" << endl;
	return ;
}

nvme_base_c::nvme_base_c( char* argv[] )
{
	//prechecking device number option
	int m_device = 0;
    cout << "nvme_base_c::nvme_base_c" << endl;
	for (int i=1; argv[i]; i++) {
		if (strcmp(argv[i],"-dev")==0 && argv[i+1]) {
			m_device = atoi(argv[i+1]);
		}
	}
	scf_init() ;
	//strcpy( m_program_name, argv[0] ) ;
}

int main()
{
	nvme_base_c insTance;
    cout << "nvme_base_c::main" << endl;
	insTance.Start(1);
	return 0;
}
