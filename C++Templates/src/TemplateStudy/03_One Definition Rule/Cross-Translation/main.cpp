#include "CrossTranslation.h"

#include <iostream>

// 템플릿의 경우
namespace
{
	void paint( Color c )
	{
		std::cout << "paint - main : " << c << std::endl;
	}
}

int main( )
{
	count1( ); // 1이 출력
	count2( ); // 1이 출력

	count_error1( ); // 2가 출력
	count_error2( ); // 3이 출력

	defaultArg1( ); // 4
	defaultArg2( ); // 3

	init( );
	highlight( red );
}