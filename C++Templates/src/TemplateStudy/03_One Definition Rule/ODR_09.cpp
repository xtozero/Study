template <typename T>
void templateFunc( T value ) { cout << value << endl; }

template void templateFunc<int>( int value );

template <>
void templateFunc( int value ) {}

int main {}