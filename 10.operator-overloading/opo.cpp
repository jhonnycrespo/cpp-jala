#include <iostream>
#include <cstdio>

using namespace std;

struct Pair
{
    int x;
    int y;
};

// Tambien funciona recibiendo (const Pair x, const Pair y)
// Entonces, porque usar referencias?? Para no crear copias de los 
// objetos y hacer el programa mas eficiente
Pair operator+(const Pair& x, const Pair& y)
{
    // Esto es posible en c++
    return Pair {x.x + y.x, x.y + y.y};
}

Pair operator*(const Pair& a, const Pair& b)
{
    return Pair {a.x * b.x, a.y * b.y};
}

int operator&&(const Pair& a, const Pair& b)
{
    return a.x + a.y + b.x + b.y;
}

ostream& operator<<(ostream& os, const Pair& pair)
{
    os << "x: " << pair.x << ", " << "y: " << pair.y << endl;

    return os;
}

int main()
{
    // ya no es necesario poner struct
    // Estos objetos se instancian en el stack
    Pair a {10, 4};
    Pair b {8, 16};

    // copyelision
    auto r = a + b;
    cout << r << endl;

    auto s = a&&b;
    printf("%d\n", s);

    auto m = a * b;
    cout << m << endl;
}