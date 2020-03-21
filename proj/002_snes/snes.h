#include <iostream>
#include "nvme_base.h"
using namespace mirne::SCF::NVME;

class nvme_basic_c : public nvme_base_c
{
	public:
		nvme_basic_c()  { return; }
		nvme_basic_c(char* argv[]) : nvme_base_c(argv), m_driver_ready(false) { return; }
		~nvme_basic_c() { return; }
		int Main( int argc, char**argv );
		bool m_driver_ready;
	protected:
		void Identify(void);
		void Start(int mode=0);
};
