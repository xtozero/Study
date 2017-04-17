template <typename T>
class C
{
	friend void f( ) {}
	friend void f( const C<T>& ) {}
};

void g( C<int>* p )
{
	f( );		// ?
	f( *p );	// ?
}

int main( )
{
	C<int>* p = nullptr;
	g( p );
}