template <typename T>
class S
{
public:
	T m;
};

// 1
unsigned long h( )
{
	// 2
	return ( unsigned long )sizeof( S<int> );
	// 3
}
// 4

int main( )
{
	h( );
}