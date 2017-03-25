#ifndef _UTIP_08_HPP_
#define _UTIP_08_HPP_

#include <iostream>

class SortTracer
{
private:
	int value;					// 저장할 정수값
	int generation;				// 추적자 생성
	static long n_created;		// 생성자 호출 횟수
	static long n_destoryed;	// 소멸자 호출 횟수
	static long n_assigned;		// 할당 횟수
	static long n_compared;		// 비교 횟수
	static long n_max_live;		// 현재 존재하는 객체의 최대 수

	// 현재 존재하는 객체의 최대 수 다시 계산
	static void update_max_live( )
	{
		if ( n_created - n_destoryed > n_max_live )
		{
			n_max_live = n_created - n_destoryed;
		}
	}

public:
	static long SortTracer::creations( )
	{
		return n_created;
	}

	static long SortTracer::destructions( )
	{
		return n_destoryed;
	}

	static long SortTracer::assignments( )
	{
		return n_assigned;
	}

	static long SortTracer::comparisions( )
	{
		return n_compared;
	}

	static long SortTracer::max_live( )
	{
		return n_max_live;
	}

	// 생성자
	SortTracer( int v = 0 ) : value( v ), generation( 1 )
	{
		++n_created;
		update_max_live( );
		std::cerr << "SortTracer #" << n_created << ", created generation " << generation << " (total: " << n_created - n_destoryed << ")\n";
	}

	// 복사 생성자
	SortTracer( const SortTracer& b ) : value( b.value ), generation( b.generation )
	{
		++n_created;
		update_max_live( );
		std::cerr << "SortTracer #" << n_created << ", copied as generation " << generation << " (total: " << n_created - n_destoryed << ")\n";
	}

	// 소멸자
	~SortTracer( )
	{
		++n_destoryed;
		update_max_live( );
		std::cerr << "SortTracer gneration" << generation << " destroyed (total: " << n_created - n_destoryed << ")\n";
	}

	// 할당
	SortTracer& operator=( const SortTracer& b )
	{
		++n_assigned;
		std::cerr << "SortTracer assignment#" << n_created << "(generation " << generation << " = " << b.generation << ")\n";
		value = b.value;
		return *this;
	}

	int val( ) const
	{
		return value;
	}

	// 비교
	friend bool operator< ( const SortTracer& a, const SortTracer& b )
	{
		++n_compared;
		std::cerr << "SortTracer comparision #" << n_compared << " (generation " << a.generation << " < " << b.generation << ")\n";
		return a.value < b.value;
	}
};

#endif
