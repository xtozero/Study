#ifndef _CROSSTRANSLATION_H
#define _CROSSTRANSLATION_H

void count1( );
void count2( );

void count_error1( );
void count_error2( );

// 인자 기본 값을 경우
void defaultArg1( );
void defaultArg2( );

// 교차 번역 단위 동등 제약 예외
const int length = 10;

class MiniBuffer
{
	char m_buf[length];
};

// 템플릿의 경우
enum Color { red, green, blue };

void init( );

template<typename T> void highlight( T x );

#include "tmp_impl.cpp"

#endif