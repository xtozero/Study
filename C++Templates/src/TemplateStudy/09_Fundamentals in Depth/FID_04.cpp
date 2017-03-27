template <typename T> class Box;

template <typename T> class Box<T>; // error

template <typename T> void translate( T* );

template <typename T> void translate<T>( T* ); // error

int main( )
{

}