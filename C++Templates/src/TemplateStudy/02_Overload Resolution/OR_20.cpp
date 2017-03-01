using FuncType = void( *)(double, int);

class IndirectFunctor
{
public:
	void operator()( double, double ) const {}
	operator FuncType( ) const { return nullptr; }
};

int main( )
{
	IndirectFunctor functor;
	functor( 3, 5 );
}