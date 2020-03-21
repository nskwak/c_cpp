#include <iostream>
#include <cstdlib>			//srand
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "unistd.h"
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <signal.h>


using namespace std;

namespace mirne {		//KNS_KK_
namespace SCF   {
namespace NVME  {

class nvme_base_c		//KK_
{
public:
   	nvme_base_c() { scf_init() ; }
   	nvme_base_c( char* argv[] ) ;
   	~nvme_base_c() { scf_close() ; return ;}
	void Start( int mode=0 ) ;
	int printf(const char *fmt, ...);
	int m_device;	
	void* MainRoutine( void ) ;
	void* AdminMainRoutine( void );
	double getTimeAsUsec();
protected:
	int LBA_Load   ( void ) ;
private:
   	void scf_init(void);
   	void scf_close(void) ;
	pthread_t m_thread_main ;

	//int printf(const char *fmt, ...);	
};

}
}
}