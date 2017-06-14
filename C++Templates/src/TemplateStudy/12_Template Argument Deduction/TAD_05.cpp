template <typename T>
class S
{
public:
	S( T b ) : a( b )
	{

	}
private:
	T a;
};

int main( )
{
	S x( 12 );
}