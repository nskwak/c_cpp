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
//using namespace mirne::SCF::NVME;

int main(int argc, char**argv)
{
	int ret;
	int device;
	int driver_ready = false;
	cout << "C++ program grammer study" << endl;
    cout << "snes.cpp - main " << endl;

	for (int i=1; argv[i]; i++) {
		if (strcmp(argv[i],"-dev")==0 && argv[i+1]) {
			device = atoi(argv[i+1]);
			i++;
			continue;
		}
	} 
  
	nvme_basic_c* nvme ; 
	nvme = new nvme_basic_c(argv) ;
	nvme->m_driver_ready = driver_ready;
	ret = nvme->Main(argc, argv); 
    return 0;
}
 
int nvme_basic_c::Main( int argc, char**argv )
{
    cout << "snes.cpp - Main " << endl;
    Start(1);
    return 0;
}

void nvme_basic_c::Start( int mode )
{
	//nvme_base_c npp;
	//npp.Start(mode); 
    cout << "snes.cpp - Start " << endl;
}

void nvme_basic_c::Identify( void )
{ 
    cout << "snes.cpp - Identify " << endl;
}
