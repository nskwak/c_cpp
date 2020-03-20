#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////////////////////
// call class by main
// https://www.bogotobogo.com/cplusplus/multipleinheritance.php
/////////////////////////////////////////////////////////////////////////

#if 0
class nvme_base_c
{
public:
    nvme_base_c();
    nvme_base_c(int mode);
    ~nvme_base_c()      {return;}
    int mode;
};

class nvme_basic_c : public nvme_base_c
{
public:
    nvme_basic_c();
    nvme_basic_c(int input) : nvme_base_c(input) {return;}      //
    ~nvme_basic_c()    { return; }
    int input;
};

nvme_base_c::nvme_base_c()
{
    cout << "1. nvme_base_c::nvme_base_c()" << endl;
}

nvme_base_c::nvme_base_c(int m)
{
    mode = m;
    cout << "2. nvme_base_c::nvme_base_c(int mode) mode= " << mode << ", m= " << m << endl;
}

nvme_basic_c::nvme_basic_c()
{
    cout << "3. nvme_basic_c::nvme_basic_c()" << endl;
}

/*
nvme_basic_c::nvme_basic_c(int m)
{
    cout << "4. nvme_basic_c::nvme_basic_c(int mode) " << m << endl;
}
*/

int main()
{
    nvme_base_c nvmebasec;   //KK_ call constructor - nvme_base_c() of nvme_base_c
    nvme_base_c nvmebasec1(1000);   //KK_ call constructor - nvme_base_c() of nvme_base_c
    cout << "nvmebasec1.mode " << nvmebasec1.mode << endl;

    nvme_basic_c nvmebasicc;
    nvme_basic_c nvmebasicc1(2000);
    cout << "nvmebasec1.mode " << nvmebasec1.mode << endl;
    
    return 0;
}
#endif

#if 0
class nvme_base_c
{
public:
    nvme_base_c();
    nvme_base_c(int mode);
    ~nvme_base_c()      {return;}
    int mode;
};

class nvme_basic_c : public nvme_base_c
{
public:
    nvme_basic_c();
    nvme_basic_c(int input);
    ~nvme_basic_c()    { return; }
    int input;
};

nvme_base_c::nvme_base_c()
{
    cout << "1. nvme_base_c::nvme_base_c()" << endl;
}

nvme_base_c::nvme_base_c(int m)
{
    mode = m;
    cout << "2. nvme_base_c::nvme_base_c(int mode)" << endl;
}

nvme_basic_c::nvme_basic_c()
{
    cout << "3. nvme_basic_c::nvme_basic_c()" << endl;
}

nvme_basic_c::nvme_basic_c(int m)
{
    cout << "4. nvme_basic_c::nvme_basic_c(int mode) " << m << endl;
}

int main()
{
    nvme_base_c nvmebasec;   //KK_ call constructor - nvme_base_c() of nvme_base_c
    nvme_base_c nvmebasec1(1000);   //KK_ call constructor - nvme_base_c() of nvme_base_c
    cout << "nvmebasec1.mode " << nvmebasec1.mode << endl;

    nvme_basic_c nvmebasicc;
    nvme_basic_c nvmebasicc1(2000);
    
    return 0;
}
#endif

#if 0
//////////////////////////////////////////////////////////////////////////////////
// easy example for constructor
// constructor is used to initialize member variable value 
//////////////////////////////////////////////////////////////////////////////////

class Circle {
	public:
		Circle();
		Circle(int rad);

		int radius;
		double getArea();
};

Circle::Circle()
{
	radius = 5;
	cout << "Circle::Circle() radius is " << radius << endl;
}

Circle::Circle(int rad)
{
	radius = rad;
	cout << "Circle::Circle(int rad) radius is " << radius << endl;
}

double Circle::getArea()
{
	return radius * radius * 3.14;
}

int main()
{
	Circle donut;
	cout << "donut.getArea() is " << donut.getArea() << endl;

	Circle pizza(10);
	cout << "pizza.getArea() is " << pizza.getArea() << endl;
	return 0;
}
#endif

#if 1
class A
{
public:
	A(int n = 1) : ia(n) 
	{ cout << "A() ia = " << ia <<  endl; }
	~A() 
	{ cout << "~A() ia = " << ia << endl; }

protected:
        int ia;
};

class B : public A
{
public:
	B(int n) : a1(new A[5]), a2(n)
	{ cout << "B()" << endl; }
	~B() 
	{ 
		cout << "~B() ia = " << ia-- << endl;
		delete[] a1;
	}

private:
	A a2;
	A* a1;
};

int main()
{
       {B b(20);}

       return 0;
}
#endif


#if 0
//////////////////////////////////////////////////////////////////////////////////
// In the following code, we have two classes A and B.
// The B is a derived class from the class A. 
// In the constructor of B, we do not specify the A-class constructor to use. 
// In the class B, we have two objects of type A as it's member.
//
// A() ia = 1
// A() ia = 20
// A() ia = 11
// B()
// ~B() ia = 1
// ~A() ia = 11
// ~A() ia = 20
// ~A() ia = 0
//
// First, the class B's constructor called the base-class A()'s default constructor which initialized ia as 1. 
// Then we initialized the two A objects: a2 with n(=20) and a1 with ai+10(=1+10). 
// Note that member initialization was done in the order of the appearance in the class definition 
// but not in the order of the initializer list.
// When object b was out of {} block scope, the destructor of B called. 
// As we see in the output, the value of the inherited member ia is 1 
// because it was constructed using default value in the A constructor. 
// Then, the two A object members of B object called two destructors with ia values of 11 and 20. 
// Finally, the base-object destructor called with ia = 0 since it was decremented by the B's destructor.
//////////////////////////////////////////////////////////////////////////////////
class A
{
public:
	A(int n = 1) : ia(n) 
	{ cout << "A() ia = " << ia <<  endl; }
	~A() 
	{ cout << "~A() ia = " << ia << endl; }

protected:
    int ia;
};

class B : public A
{
public:
	B(int n) : a1(ia+10), a2(n)
	{ cout << "B()" << endl; }
	~B() 
	{ cout << "~B() ia = " << ia-- << endl; }

private:
	A a2;
	A a1;
};

int main()
{
	{ B b(20); }

        return 0;
}
#endif

#if 0
//////////////////////////////////////////////////////////////////////////////////
// If we need to initialize inherited the base-class member with different value form a default value, 
// we can use base-class constructor in the initializer list of the derived-class constructor. 
// Let's say, if we want to set the inherited member as 12 not the default value of 1. 
// Then, we use the following line of code for the initializer.
//////////////////////////////////////////////////////////////////////////////////
class A
{
public:
	A(int n = 1) : ia(n) 
	{ cout << "A() ia = " << ia <<  endl; }

protected:
    int ia;
};

class B : public A
{
public:
	B(int n) : ib(n), A(n+10)
	{ cout << "B()" << endl; }

private:
    int ib;
};

int main()
{
    B b(2);

    return 0;
}
#endif

#if 0
/////////////////////////////////////////////////////////////////////////////////////////////
// a derived-class constructor always calls a base-class constructor.
// As we see from the result, the derived-class constructor calls the base-class constructor.
// Actually, the base-class object should be constructed before the code enters the body of 
// the derived-class constructor.
/////////////////////////////////////////////////////////////////////////////////////////////
class A
{
public:
	A(int n = 1) : ia(n) { cout << "A()" << endl; }

protected:
    int ia;
};

class B : public A
{
public:
	B(int n) : ib(n) { cout << "B()" << endl; }

private:
    int ib;
};

int main()
{
    B b(3);

    return 0;
}
#endif


#if 0
class A
{
public:
	void foo() const { std::cout << "A" << std::endl; }
};

class B
{
public:
	void foo() const { std::cout << "B" << std::endl; }
};

class C : public A, public B
{
public:	
	using A::foo;  // note that this is private section 
};

int main()
{
	B b;
	b.foo();  // OK: B::foo()

	C c;
	c.foo();   // error: A::foo() or private member in class 'C'

	return 0;
} 
#endif

#if 0
class A
{
public:
	int xPublic;
	void classApublicfunc();
protected:
	int xProtected;	
private:
	int xPrivate;
};

class B : public A
{
public:
	void foo(A *a, B *b)
	{
		//a->xProtected = 0.0;     // error: A::xProtected inaccessible
		b->xProtected = 0.0;     // OK: inherited member
		this->xProtected = 0.0;
	}
};

void A::classApublicfunc()
{
	xPublic = 2;
	std::cout << "A::classApublicfunc " << " " << xPublic << std::endl;
}

int main(int argc, char** argv)
{
	A a;
	B b;
	//b.xProtected = 0.0;	// error: inaccessible outside of a class - inherited xProtected 
	b.foo(&a, &b);
	a.classApublicfunc();

	return 0;
}
#endif



#if 0
//////////////////////////////////////////////////////////////
// Inheritance: member access
// 1. All members are inherited to the derived class.
// 2. But the private member of the base class is not directly accessible.
// 3. The inherited private member of a base class can be accessed via inherited public member function. 
//    In other words, it has to work through the base-class method.
// 4. Public member of a base class inherited as a public member.

class A					//KK_ public nvme_base_c
{
public:
	int xPublic;
	void classApublicfunc();
protected:
	int xProtected;	
	void classAprotectedfunc();
private:
	int xPrivate;
	void classAprivatefunc();
};

class B : public A		//KK_ class nvme_basic_c : public nvme_base_c
{
public:
	void classBpublicfunc(); 	
};

void B::classBpublicfunc()
{
	xProtected = 1;
	//xPrivate = 2;
	//std::cout << "A::classBspublicfunc " << xProtected << " " << xPrivate << std::endl;
	std::cout << "A::classBpublicfunc " << " " << xProtected << " " << std::endl;
}

void A::classApublicfunc()
{
	xProtected = 1;
	xPrivate = 2;
	std::cout << "A::classApublicfunc " << " " << xProtected << " " << xPrivate << std::endl;
}

void A::classAprotectedfunc()
{
	xProtected = 3;
	xPrivate = 4;
	std::cout << "A::classAprotectedfunc " << " " << xProtected << " " << xPrivate << std::endl;
}

void A::classAprivatefunc()
{
	xProtected = 5;
	xPrivate = 6;
	std::cout << "A::classAprivatefunc " << " " << xProtected << " " << xPrivate << std::endl;
}


int main(int argc, char** argv)
{
	A a;
	a.xPublic = 0;
	a.classApublicfunc();
	//a.classAprotectedfunc();	// error: inaccessible
	//a.classAprivatefunc();		// error: inaccessible

	//a.xProtected = 0; 		// error: inaccessible
	//a.xPrivate = 0;   		// error: inaccessible

	B b;
	b.xPublic = 0;
	b.classApublicfunc();
	b.classBpublicfunc();
	//b.classAprotectedfunc();	// error: inaccessible
	//b.classAprivatefunc();		// error: inaccessible

	//b.xProtected = 0;  		// error: inaccessible
	//b.xPrivate = 0;    		// error: inaccessible

 	return 0;       
}
#endif

