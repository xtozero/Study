template <typename T>
class Outside
{
public:
	template <typename U>
	class Inside
	{
	};
};

template <>
class Outside<void>
{
	template <typename U>
	class Inside
	{
	private:
		static int count;
	};
};

template <typename U>
int Outside<void>::Inside<U>::count = 1;

// ��ü Ư��ȭ�� �Ϲ� ���ø� �ν��Ͻ��� ������ ���
template <typename T>
class Invalid
{

};

Invalid<double> x1;

template<>
class Invalid<double>; // error : �̹� �ν��Ͻ�ȭ ����