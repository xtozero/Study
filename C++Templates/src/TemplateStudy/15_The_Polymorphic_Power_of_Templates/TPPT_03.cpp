#include <algorithm>

template <typename Iterator>
Iterator max_element( Iterator begin, Iterator end )
{
	Iterator max = begin;

	for ( Iterator i = ++begin; i != end; ++i )
	{
		if ( *max < *i )
		{
			max = i;
		}
	}

	return max;
}

template <typename T, typename Iterator>
class list
{
public:
	typedef Iterator const_iterator;

	const_iterator begin( ) const;
	const_iterator end( ) const;
};
