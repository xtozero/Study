#pragma once

// 3. static 데이터 멤버는 프로그램당 한번만 정의돼야 한다.
class GlobalCounter
{
private:
	static int m_counter;
};

// 4. 인라인이 아닌 함수 템플릿이 export와 함께 선언됐을 경우
// export된 템플릿은 현재 c++ 표준이 아니라는 에러가 발생 error C3348
//export
//template<typename T>
//T Add( T lhs, T rhs );

// 5. 클래스 템플릿의 정적 데이터 멤버가 export로 선언됐을 경우
// export된 템플릿은 현재 c++ 표준이 아니라는 에러가 발생 error C3348
//template <typename T>
//class ClassTemplate
//{
//private:
//	static int m_counter;
//};
//
//export template <typename T>
//int ClassTemplate<T>::m_counter = 0;