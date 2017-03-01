template <typename T>
class Implicit
{
public:
	Implicit( T a ) { }
};

template <typename T>
void TemplateFunction( Implicit<T> ) {}

int main( )
{
	TemplateFunction<int>( 1 );
	TemplateFunction( 1 );
}