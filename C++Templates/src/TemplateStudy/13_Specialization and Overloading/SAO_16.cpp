template <typename T, int I = 3>
class S;							// �⺻ ���ø�

template <typename T>
class S<int, T>;					// error : �Ķ���� ���� ����ġ

template <typename T = int>
class S<T, 10>;						// error : �⺻���� ��� �Ұ�

template <int I>
class S<int, I * 2>;				// error : ���������� �ƴ� ǥ������ ������� ����

template <typename U, int X>
class S<U, X>						// error : �⺻ ���ø��� ���� ����