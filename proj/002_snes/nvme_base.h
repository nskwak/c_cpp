#include <iostream>
using namespace std;

//namespace mirne {		//KNS_KK_
//namespace SCF   {
//namespace NVME  {

class nvme_base_c		//KK_
{
public:
   	nvme_base_c() { scf_init() ; }
   	nvme_base_c( char* argv[] ) ;
   	~nvme_base_c() { scf_close() ; return ;}
	void Start( int mode=0 ) ;

private:
   	void scf_init(void);
   	void scf_close(void) ;
};

//}
//}
//}