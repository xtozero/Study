#pragma once

#include <type_traits>

template <typename T>
class IsFundaT : public std::false_type {};

#define MK_FUNDA_TYPE(T) \
template <> class IsFundaT<T> : public std::true_type {};

MK_FUNDA_TYPE( void );

MK_FUNDA_TYPE( bool );
MK_FUNDA_TYPE( char );
MK_FUNDA_TYPE( signed char );
MK_FUNDA_TYPE( unsigned char );
MK_FUNDA_TYPE( wchar_t );
MK_FUNDA_TYPE( char16_t );
MK_FUNDA_TYPE( char32_t );

MK_FUNDA_TYPE( signed short );
MK_FUNDA_TYPE( unsigned short );
MK_FUNDA_TYPE( signed int );
MK_FUNDA_TYPE( unsigned int );
MK_FUNDA_TYPE( signed long );
MK_FUNDA_TYPE( unsigned long );
MK_FUNDA_TYPE( signed long long );
MK_FUNDA_TYPE( unsigned long long );

MK_FUNDA_TYPE( float );
MK_FUNDA_TYPE( double );
MK_FUNDA_TYPE( long double );

MK_FUNDA_TYPE( std::nullptr_t );

#undef MK_FUNDA_TYPE
