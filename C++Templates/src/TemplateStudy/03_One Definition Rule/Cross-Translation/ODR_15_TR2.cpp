#include "ODR_15.h"

static int counter = 0;

// ���� ���� 1�� increase_counter�� ��Ȯ�� ���� ��ū�� ������ ������
// static int counter�� ���� ������ ���� ���� �ٸ� ��ü�̱� ������ ������ ������ �߻��Ѵ�.
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