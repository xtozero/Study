#include <iostream>

class EmptyClass
{
};

class Empty 
{
	using Int = int;
};

class EmptyTwo : public Empty
{
};

class EmptyThree : public EmptyTwo
{
};

class NonEmpty : public Empty, public EmptyTwo
{
};

int main( )
{
	std::cout << "sizeof(EmptyClass) : " << sizeof( EmptyClass ) << std::endl;

	std::cout << "sizeof( Empty ) : " << sizeof( Empty ) << std::endl;
	std::cout << "sizeof( EmptyTwo ) : " << sizeof( EmptyTwo ) << std::endl;
	std::cout << "sizeof( EmptyThree ) : " << sizeof( EmptyThree ) << std::endl;

	std::cout << "sizeof( NonEmpty ) : " << sizeof( NonEmpty ) << std::endl;
}