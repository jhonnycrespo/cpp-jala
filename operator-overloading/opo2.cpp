#include <cstdio>

/**
 * Se pueden sobrecargar todos los operadores, excepto: ::, ., sizof, typeid, ? :
 */

int main()
{
    int x = 6;
    auto y = 7;
    auto r = x + y;
    // auto s = operator+(x, y);

    // printf("%d\n", s);
}