#include <string>

template <typename T>
const T& max( const T& lhs, const T& rhs )
{
	return lhs < rhs ? rhs : lhs;
}

//template <typename T>
//const T max( const T lhs, const T rhs )
//{
//	return lhs < rhs ? rhs : lhs;
//}

template <typename T, int N, int M>
const T* max( const T (&lhs)[N], const T (&rhs)[M] )
{
	return lhs < rhs ? rhs : lhs;
}


int main( )
{
	max( "apple", "peach" ); // 모호한 호출
}