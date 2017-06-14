template <typename T>
void f1( T, T ) {}

void( *pf )( char, char ) = &f1;

class S
{
public:
	template <typename T> operator T&( ) {}
};

void f2( int (&)[20] ) {}

void g( S s )
{
	f2( s );
}

int main()
{
}