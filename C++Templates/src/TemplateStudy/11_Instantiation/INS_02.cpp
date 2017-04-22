template <typename T>
class Safe {};

template <int N>
class Danger
{
public:
	typedef char Block[N];		// N <= 0 이면 실패
};

template <typename T, int N>
class Tricky
{
public:
	virtual ~Tricky( ) {}

	void no_body_here( Safe<T> = 3 );
	void inclass( )
	{
		Danger<N> no_boom_yet;
	}
	void error() { Danger<0> boom; }
	// void unsafe( T( *p )[N] );
	T operator->( );
	// virtual Safe<T> suspect( );
	struct Nested
	{
		Danger<N> pfew;
	};
	union						// 익명 공용체
	{
		int align;
		Safe<T> anonymous;
	};
};

int main( )
{
	Tricky<int, 0> ok;
}