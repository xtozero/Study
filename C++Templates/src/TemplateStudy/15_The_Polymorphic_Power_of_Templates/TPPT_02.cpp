#include <iostream>
#include <vector>

class Coord
{
public:
	Coord abs( ) { return Coord( ); }
	Coord operator-( const Coord& ) { return Coord( ); }
};

class Circle
{
public:
	void draw( ) const { std::cout << "Circle::draw" << std::endl; }
	Coord center_of_gravity( ) const { return Coord( ); }
};

class Line
{
public:
	void draw( ) const { std::cout << "Line::draw" << std::endl; }
	Coord center_of_gravity( ) const { return Coord( ); }
};

template <typename GeoObj>
void myDraw( const GeoObj& obj )
{
	obj.draw( );
}

template <typename GeoObj1, typename GeoObj2>
Coord distance( const GeoObj1& x1, const GeoObj2& x2 )
{
	Coord c = x1.center_of_gravity( ) - x2.center_of_gravity( );
	return c.abs( );
}

template <typename GeoObj>
void drawElems( const std::vector<GeoObj>& elems )
{
	for ( size_t i = 0; i < elems.size( ); ++i )
	{
		elems[i].draw( );
	}
}

int main( )
{
	Line l;
	Circle c, c1, c2;

	myDraw( l );
	myDraw( c );

	distance( c1, c2 );
	distance( l, c );

	std::vector<Line> coll;

	coll.push_back( l );

	drawElems( coll );
}