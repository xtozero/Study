#ifndef _CROSSTRANSLATION_H
#define _CROSSTRANSLATION_H

void count1( );
void count2( );

void count_error1( );
void count_error2( );

// ���� �⺻ ���� ���
void defaultArg1( );
void defaultArg2( );

// ���� ���� ���� ���� ���� ����
const int length = 10;

class MiniBuffer
{
	char m_buf[length];
};

// ���ø��� ���
enum Color { red, green, blue };

void init( );

template<typename T> void highlight( T x );

#include "tmp_impl.cpp"

#endif