#pragma once


template <typename T>
class Holder
{
private:
	T* ptr = nullptr;

public:
	explicit Holder( T* p ) : ptr( p ) {}

	~Holder( )
	{
		delete ptr;
	}

	Holder<T>& operator=( T* p )
	{
		delete ptr;
		ptr = p;
		return *this;
	}

	T& operator*( ) const
	{
		return *ptr;
	}

	T* operator->( ) const
	{
		return ptr;
	}

	T* get( ) const
	{
		return ptr;
	}

	T* release( )
	{
		T* ret = ptr;
		ptr = nullptr;
		return ret;
	}

	void exchange_with( Holder<T>& h )
	{
		std::swap( ptr, h.ptr );
	}

	void exchange_with( T*& p )
	{
		std::swap( ptr, p )
	}

	Holder( Holder<T>&& h )
	{
		ptr = h.ptr;
		h.ptr = nullptr;
	}

	Holder<T>& operator=( Holder<T>&& h )
	{
		ptr = h.ptr;
		h.ptr = nullptr;
		return *this;
	}

private:
	Holder( const Holder<T>& );
	Holder<T>& operator=( const Holder<T>& );
};