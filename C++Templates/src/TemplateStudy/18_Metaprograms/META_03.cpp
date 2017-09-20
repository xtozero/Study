#include <iostream>

template <int N, int LO = 1, int HI=N>
class Sqrt
{
public:
	enum { mid = (LO+HI+1) / 2 };
	enum { result = (N<mid*mid) ? Sqrt<N, LO, mid-1>::result : Sqrt<N, mid, HI>::result };
};

template <int N, int M>
class Sqrt<N, M, M>
{
public:
	enum { result = M };
};

int main( )
{
	std::cout << "Sqrt<16>::result = " << Sqrt<16>::result << std::endl;
	std::cout << "Sqrt<25>::result = " << Sqrt<25>::result << std::endl;
	std::cout << "Sqrt<42>::result = " << Sqrt<42>::result << std::endl;
	std::cout << "Sqrt<1>::result = " << Sqrt<1>::result << std::endl;
}