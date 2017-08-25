#include <array>
#include <iostream>

template <typename T1, typename T2>
class Promotion;

template <bool C, typename Ta, typename Tb>
class IfThenElse;

template <typename Ta, typename Tb>
class IfThenElse<true, Ta, Tb>
{
public:
	using ResultT = Ta;
};

template <typename Ta, typename Tb>
class IfThenElse<false, Ta, Tb>
{
public:
	using ResultT = Tb;
};

template <typename T1, typename T2>
class Promotion
{
public:
	using ResultT = typename IfThenElse<( sizeof( T1 ) > sizeof( T2 ) ),
										T1,
										typename IfThenElse<( sizeof( T1 ) < sizeof( T2 ) ), T2, void>::ResultT
										>::ResultT;
};

template <typename T>
class Promotion<T, T>
{
public:
	using ResultT = T;
};

#define MK_PROMOTION( T1, T2, Tr )			\
template <> class Promotion<T1, T2>			\
{											\
public:										\
	using ResultT = Tr;						\
};											\
											\
template <> class Promotion<T2, T1>			\
{											\
public:										\
	using ResultT = Tr;						\
};											\

MK_PROMOTION( bool, char, int )
MK_PROMOTION( bool, unsigned char, int )
MK_PROMOTION( bool, signed char, int )

template <typename T1, typename T2, int N>
class Promotion<std::array<T1, N>, std::array<T2, N>>
{
public:
	using ResultT = std::array<typename Promotion<T1, T2>::ResultT, N>;
};

template <typename T1, typename T2, int N>
std::array<typename Promotion<T1, T2>::ResultT, N> operator+( const std::array<T1, N>& lhs, const std::array<T2, N>& rhs )
{
	std::array<typename Promotion<T1, T2>::ResultT, N> result;

	for ( int i = 0; i < N; ++i )
	{
		result[i] = lhs[i] + rhs[i];
	}

	return result;
}

//template <typename T1, typename T2, int N>
//typename Promotion<std::array<T1, N>, std::array<T2, N>>::ResultT operator+( const std::array<T1, N>& lhs, const std::array<T2, N>& rhs )
//{
//	typename Promotion<std::array<T1, N>, std::array<T2, N>>::ResultT result;
//
//	for ( int i = 0; i < N; ++i )
//	{
//		result[i] = lhs[i] + rhs[i];
//	}
//
//	return result;
//}

int main( )
{
	std::array<int, 10> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::array<char, 10> b = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	auto result = a + b;

	for ( auto elem : result )
	{
		std::cout << elem << ' ';
	}

	std::cout << std::endl;
}