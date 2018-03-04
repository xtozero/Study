#include "copycounter.h"
#include "TupleAlgorithm.h"

#include <string>
#include <complex>

template<typename T, typename U>
class SmallerThanT
{
public:
	static constexpr bool value = sizeof( T ) < sizeof( U );
};

int main( )
{
	auto t1 = pushFront( makeTuple( 17, 3.14, "Hello World!" ), 16 );
	std::cout << t1 << std::endl;

	auto t2 = pushBack( makeTuple( 17, 3.14, "Hello" ), std::string( "Template!" ) );
	std::cout << t2 << std::endl;

	auto t3 = popFront( pushBack( Tuple<int, double, std::string>( 17, 3.14, "Hello, World!" ), true ) );
	std::cout << t3 << std::endl;

	auto t4 = reverse( makeTuple( 1, 2.5, std::string( "hello" ) ) );
	std::cout << t4 << std::endl;

	auto t5 = popBack( makeTuple( 1, 2.5, std::string( "hello" ) ) );
	std::cout << t5 << std::endl;

	Tuple<CopyCounter<0>, CopyCounter<1>, CopyCounter<2>, CopyCounter<3>, CopyCounter<4>> copies;
	auto t6 = reverse( copies );
	std::cout << "0: " << CopyCounter<0>::numCopies << " copies\n";
	std::cout << "1: " << CopyCounter<1>::numCopies << " copies\n";
	std::cout << "2: " << CopyCounter<2>::numCopies << " copies\n";
	std::cout << "3: " << CopyCounter<3>::numCopies << " copies\n";
	std::cout << "4: " << CopyCounter<4>::numCopies << " copies\n";

	CopyCounter<0>::numCopies = 0;
	CopyCounter<1>::numCopies = 0;
	CopyCounter<2>::numCopies = 0;
	CopyCounter<3>::numCopies = 0;
	CopyCounter<4>::numCopies = 0;

	auto t7 = makeTuple( get<4>( copies ), get<3>( copies ), get<2>( copies ), get<1>( copies ), get<0>( copies ) );
	std::cout << "0: " << CopyCounter<0>::numCopies << " copies\n";
	std::cout << "1: " << CopyCounter<1>::numCopies << " copies\n";
	std::cout << "2: " << CopyCounter<2>::numCopies << " copies\n";
	std::cout << "3: " << CopyCounter<3>::numCopies << " copies\n";
	std::cout << "4: " << CopyCounter<4>::numCopies << " copies\n";

	using MyIndexList = Reverse<MakeIndexList<5>>;

	Tuple<int, double, std::string> t8( 42, 7.7, "hello" );
	auto a = splat<1, 4>( t8 );
	std::cout << a << std::endl;

	auto t9 = makeTuple( 17LL, std::complex<double>( 42, 77 ), 'c', 42, 7.7 );
	std::cout << t1 << std::endl;
	auto t10 = sort<SmallerThanT>( t1 );
	std::cout << "sorted by size: " << t2 << std::endl;
}