template <const char* msg>
class Diagnoser
{
public:
	void print( ) {}
};

template <double Ratio>
class Converter
{
public:
	static double convert( double val )
	{
		return val * Ratio;
	}
};

typedef Converter<0.0254> InchToMeter;

int main( )
{
	Diagnoser<"Surprise!">( ).print( );
}
