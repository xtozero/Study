#pragma once

template <typename... Types>
class Tuple;

template <typename Head, typename... Tail>
class Tuple<Head, Tail...> : private Tuple<Tail...>
{
private:
	Head head;

public:
	Head& getHead( ) { return head; }
	const Head& getHead( ) const { return head; }
	Tuple<Tail...>& getTail( ) { return *this; }
	const Tuple<Tail...>& getTail( ) const { return *this; }
};