#include "OnePerPorgram.h"

// 1. �ζ����� �ƴ� �Լ��� �ζ����� �ƴ� ��� �Լ��� ���α׷��� �� ���� ���ǵž� �Ѵ�.
// ���� �Լ� ����� ������ inline�� ����� ����
inline int Add( int lhs, int rhs )
{
	return lhs + rhs;
}

// 2. �ܺ� ������ ���� ������ ���α׷��� �� ���� ���ǵž� �Ѵ�.
int counter;

// 3. ���� ������ ����� ���α׷��� �� ���� ���ǵž� �Ѵ�.
int GlobalCounter::m_counter = 0;