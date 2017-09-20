struct TrueConstants
{
	enum { Three = 3 };
	static const int Four = 4;
	static constexpr int Five = 5;
};

void foo( const int& )
{

}

int main( )
{
	foo( TrueConstants::Three );
}