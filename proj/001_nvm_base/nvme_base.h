#include <iostream>
using namespace std;

namespace mirne {		
namespace SCF   {
namespace NVME  {

	class nvme_base_c		//KK_
	{
    	public:
	    	nvme_base_c() { cout << "nvme_base_c in class nvme_base_c" << endl; scf_init() ; }
	    	nvme_base_c( char* argv[] ) ;
	    	virtual ~nvme_base_c() { scf_close() ; return ;}
			virtual void Start( int mode=0 ) ;
    	private:
	    	void scf_init( void );
        	void scf_close( void ) ;
	};

}   //NVME
}   //SCF
}   //mirne
