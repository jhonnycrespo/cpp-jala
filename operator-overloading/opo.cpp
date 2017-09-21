#include <cstdio>

struct Pair
{
    int x;
    int y;
};

Pair operator+(const Pair& x, const Pair& y)
{
    // Esto es posible en c++
    return Pair {x.x + y.x, x.y + y.y};
}

int operator&&(const Pair& a, const Pair& b)
{
    return a.x + a.y + b.x + b.y;
}

int main()
{
    // ya no es necesario poner struct
    // Estos objetos se instancian en el stack
    Pair a {10, 4};
    Pair b {8, 16};

    // copyelision
    auto r = a + b;
    printf("%d %d\n", r.x, r.y);

    auto s = a&&b;
    printf("%d\n", s);
}