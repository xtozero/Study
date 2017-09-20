#include <type_traits>

template <int N, int I = 1>
class Sqrt
{
public:
	enum { result = ( I * I < N ) ? Sqrt<N, I+1>::result : I };
};

template <int N>
class Sqrt<N, N>
{
public:
	enum { result = N };
};

// conditional version
/*
template <int N>
class Value
{
public:
	enum { result = N };
};

template <int N, int I = 1>
class Sqrt
{
public:
	using SubT = typename std::conditional<( I * I < N ), Sqrt<N, I + 1>, Value<I>>::type;

	enum { result = SubT::result };
};
*/

int main( )
{
	Sqrt<16>::result;
}