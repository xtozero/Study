#include <array>
#include <iostream>
#include <type_traits>
#include <vector>

template <typename T>
void f1( T* ) {}

template <typename E, int N>
void f2( E( &)[N] ) {}

template <typename T1, typename T2, typename T3>
void f3( T1( T2::* )( T3* ) ) {}

class S
{
public:
	void f( double* ) {}
};

template <typename T>
class Q
{
public:
	using Type = T;
};

template <typename T>
void f4( typename Q<T>::Type arg ) {}

template <typename T>
void f5( decltype( *std::declval<T>( ) ) arg ) {}

template <std::size_t N>
void f6( std::array<int, 2 * N> arg ) {}

template<typename T, typename F>
void f7( const std::vector<T>& v, const F& comp = std::less<T>( ) );

template<typename T> 
void f8( const T& value ) { std::cout << value; }

template<class T> void f9( std::vector<T> ) {}
template<class T> void f10( std::vector<T>, T x ) {}

template<class... Ts, class T> void f11( T n, Ts... args ) {}
template<class... Ts, class T> void f12( Ts... args, T n ) {}

template<int i> void f13( int arg[10][i] ) {}
template<int i> void f14( int arg[i][20] ) {}
template<int i> void f15( int( &arg )[i][20] ) {}

int main( )
{
	int*** a = nullptr;
	f1( a );		// T를 int**로 추론

	bool b[42];
	f2( b );		// E는 bool로 N은 42로 추론
	f3( &S::f );	// T1 = void , T2 = S, T3 = double

	// 1
	Q<int>::Type c;
	f4( c );

	// 2
	int d;
	f5( d );

	// 3
	std::array<int, 10> e;
	f6( e );

	// 4
	std::vector<std::string> v( 3 );
	f7( v );

	// 5
	f8( "123" );
	f8( std::endl );

	// 6
	f9( { 1, 2, 3 } );
	f10( { 1, 2, 3 }, 10 );

	// 7
	f11( 1, 2, 3, 4 );
	f12( 1, 2, 3, 4 );

	// 8
	int m[10][20];
	f13( m );     // OK: deduced i = 20
	f13<20>( m ); // OK
	f14( m );     // error: i is non-deduced context
	f14<10>( m ); // OK
	f15( m );     // OK: deduced i = 10
	f15<10>( m ); // OK
}