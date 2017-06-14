template <typename T>
void init( T* loc, T const& val = T( ) )
{
	*loc = val;
}

class S
{
public:
	S( int, int ) {}
};

S s( 0, 0 );

template <typename T>
void f( T x = 42 ) {}

int main( )
{
	init( &s, S( 7, 42 ) );

	f<int>( );		// ok : T=int
	f( );			// error
}