template <typename T, int I = 3>
class S;							// 기본 템플릿

template <typename T>
class S<int, T>;					// error : 파라미터 종류 불일치

template <typename T = int>
class S<T, 10>;						// error : 기본인자 사용 불가

template <int I>
class S<int, I * 2>;				// error : 데이터형이 아닌 표현식을 허용하지 않음

template <typename U, int X>
class S<U, X>						// error : 기본 템플릿과 차이 없음