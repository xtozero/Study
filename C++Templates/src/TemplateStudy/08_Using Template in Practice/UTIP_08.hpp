#ifndef _UTIP_08_HPP_
#define _UTIP_08_HPP_

#include <iostream>

class SortTracer
{
private:
	int value;					// ������ ������
	int generation;				// ������ ����
	static long n_created;		// ������ ȣ�� Ƚ��
	static long n_destoryed;	// �Ҹ��� ȣ�� Ƚ��
	static long n_assigned;		// �Ҵ� Ƚ��
	static long n_compared;		// �� Ƚ��
	static long n_max_live;		// ���� �����ϴ� ��ü�� �ִ� ��

	// ���� �����ϴ� ��ü�� �ִ� �� �ٽ� ���
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

	// ������
	SortTracer( int v = 0 ) : value( v ), generation( 1 )
	{
		++n_created;
		update_max_live( );
		std::cerr << "SortTracer #" << n_created << ", created generation " << generation << " (total: " << n_created - n_destoryed << ")\n";
	}

	// ���� ������
	SortTracer( const SortTracer& b ) : value( b.value ), generation( b.generation )
	{
		++n_created;
		update_max_live( );
		std::cerr << "SortTracer #" << n_created << ", copied as generation " << generation << " (total: " << n_created - n_destoryed << ")\n";
	}

	// �Ҹ���
	~SortTracer( )
	{
		++n_destoryed;
		update_max_live( );
		std::cerr << "SortTracer gneration" << generation << " destroyed (total: " << n_created - n_destoryed << ")\n";
	}

	// �Ҵ�
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

	// ��
	friend bool operator< ( const SortTracer& a, const SortTracer& b )
	{
		++n_compared;
		std::cerr << "SortTracer comparision #" << n_compared << " (generation " << a.generation << " < " << b.generation << ")\n";
		return a.value < b.value;
	}
};

#endif
