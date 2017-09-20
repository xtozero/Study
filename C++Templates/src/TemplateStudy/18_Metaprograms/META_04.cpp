#include <type_traits>

template <int N, int LO = 1, int HI = N>
class Sqrt
{
public:
	enum { mid = ( LO + HI + 1 ) / 2 };

	using SubT = typename std::conditional < N<mid*mid, Sqrt<N, LO, mid - 1>, Sqrt<N, mid, HI>>::type;

	enum { result = SubT::result };
};

template <int N, int M>
class Sqrt<N, M, M>
{
public:
	enum { result = M };
};

int main( )
{
	Sqrt<4>::result;
}