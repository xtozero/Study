class Base
{
public:
	operator short( ) const { return 0; }
};

class Derived : public Base
{

};

void count( int ) {}

int main( )
{
	Derived object;
	count( object );
}