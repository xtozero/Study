#include "CrossTranslation.h"

#include <iostream>

// ���ø��� ���
namespace
{
	void paint( Color c )
	{
		std::cout << "paint - main : " << c << std::endl;
	}
}

int main( )
{
	count1( ); // 1�� ���
	count2( ); // 1�� ���

	count_error1( ); // 2�� ���
	count_error2( ); // 3�� ���

	defaultArg1( ); // 4
	defaultArg2( ); // 3

	init( );
	highlight( red );
}