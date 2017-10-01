#include "SArray.h"

int main( )
{
	SArray<double> x( 1000 ), y( 1000 );

	x = 1.2 * x + x * y;
}