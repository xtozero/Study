#pragma once

// 3. static ������ ����� ���α׷��� �ѹ��� ���ǵž� �Ѵ�.
class GlobalCounter
{
private:
	static int m_counter;
};

// 4. �ζ����� �ƴ� �Լ� ���ø��� export�� �Բ� ������� ���
// export�� ���ø��� ���� c++ ǥ���� �ƴ϶�� ������ �߻� error C3348
//export
//template<typename T>
//T Add( T lhs, T rhs );

// 5. Ŭ���� ���ø��� ���� ������ ����� export�� ������� ���
// export�� ���ø��� ���� c++ ǥ���� �ƴ϶�� ������ �߻� error C3348
//template <typename T>
//class ClassTemplate
//{
//private:
//	static int m_counter;
//};
//
//export template <typename T>
//int ClassTemplate<T>::m_counter = 0;