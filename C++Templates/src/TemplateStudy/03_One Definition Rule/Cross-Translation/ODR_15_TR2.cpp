#include "ODR_15.h"

static int counter = 0;

// 번역 단위 1의 increase_counter와 정확히 같은 토큰을 가지고 있지만
// static int counter는 내부 연결을 갖는 서로 다른 실체이기 때문에 미정의 동작이 발생한다.
inline void increase_counter( )
{
	++counter;
	std::cout << counter << std::endl;
	std::cout << &counter << std::endl;
}

inline void increase_counter2( )
{
	++counter;
	std::cout << counter << std::endl;
	std::cout << &counter << std::endl;
}

void count2( )
{
	increase_counter2( );
}

void count_error2( )
{
	increase_counter( );
}