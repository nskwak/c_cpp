#include <iostream>
using namespace std;

namespace mirne {		
namespace SCF   {
namespace NVME  {

class nvme_base_c		//KK_
{
    public:
	    nvme_base_c() { scf_init() ; }
};

}   //NVME
}   //SCF
}   //mirne

using namespace mirne::SCF::NVME;

classA::classAPublicSubfunc1()
{
    printf("classAPublicSubfunc1\n");
}

int main()
{
    std::cout << "Hello World! " << std::endl;     // prints Hello World!
    cout << "I'm a C++ program" << endl; // prints I'm a C++ program
    classA::classAPublicSubfunc1();
    return 0;
}
