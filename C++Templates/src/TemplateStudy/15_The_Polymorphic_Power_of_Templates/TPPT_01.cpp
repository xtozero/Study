#include <iostream>
#include <vector>

class Coord
{
public:
	Coord abs( ) { return Coord( ); }
	Coord operator-( const Coord& ) { return Coord( ); }
};

class GeoObj
{
public:
	virtual void draw( ) const = 0;
	virtual Coord center_of_gravity( ) const = 0;
};

class Circle : public GeoObj
{
public:
	virtual void draw( ) const override { std::cout << "Circle::draw" << std::endl; }
	virtual Coord center_of_gravity( ) const override { return Coord( ); }
};

class Line : public GeoObj
{
public:
	virtual void draw( ) const override { std::cout << "Line::draw" << std::endl; }
	virtual Coord center_of_gravity( ) const override { return Coord( ); }
};

void myDraw( const GeoObj& obj )
{
	obj.draw( );
}

Coord distance( const GeoObj& x1, const GeoObj& x2 )
{
	Coord c = x1.center_of_gravity( ) - x2.center_of_gravity( );
	return c.abs( );
}

void drawElems( const std::vector<GeoObj*>& elems )
{
	for ( size_t i = 0; i < elems.size( ); ++i )
	{
		elems[i]->draw( );
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

	std::vector<GeoObj*> coll;

	coll.push_back( &l );
	coll.push_back( &c );

	drawElems( coll );
}