#include <cstdio>

struct X
{
    int n;

    ~X()
    {
        printf("%d\n", n);
    }
};


int main()
{
    // El compilador reconoce que 20, 8, 4, ... son de tipo X. 
    // El destructor se llama del final al principio.
    X xs[] = {20, 8, 4, 6, 1};

    // al acceder a un elemento del array, devuelve referencia.
    X& z = xs[2];
}