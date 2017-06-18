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

// 전체 특수화와 일반 템플릿 인스턴스가 공존할 경우
template <typename T>
class Invalid
{

};

Invalid<double> x1;

template<>
class Invalid<double>; // error : 이미 인스턴스화 됐음