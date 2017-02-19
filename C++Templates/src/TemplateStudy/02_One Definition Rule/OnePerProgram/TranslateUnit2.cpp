#include "OnePerPorgram.h"

// 1. 인라인이 아닌 함수와 인라인이 아닌 멤버 함수는 프로그램당 한번만 정의돼야 한다.
// 관련 함수 선언과 정의의 inline을 지우면 에러
inline int Add( int lhs, int rhs )
{
	return lhs + rhs;
}

// 2. 외부 연결을 같는 변수는 프로그램당 한 번만 정의돼야 한다.
// 아래 주석을 풀면 TranslateUnit1.cpp의 정의와 충돌
//int counter;

// 3. 정적 데이터 멤버는 프로그램당 한 번만 정의돼야 한다.
// 아래 주석을 풀면 TranslateUnit1.cpp의 정의와 충돌
// int GlobalCounter::m_counter = 0;