#include <iostream>

using namespace std;

/**
 * Function Objects - Functors
 * 
 * Los punteros a funciones no manejan estado. Y q pasa si quisieramos tener informacion de estado?
 *
 * Un fuctor es un objecto que se comporta como si fuera funcion. Y puede contener estado.
 * 
 */

// como es struct, no es necesario ponerle constructor (revisar esto)
struct RangePrinter
{
    int min, max;

    // sobrecargamos el operador ()
    void operator()(int a, int b) const
    {
        if (a >= min && a <= max)
            printf("%d\n", a);

        if (b >= min && b <= max)
            printf("%d\n", b);
    }
};

void s(int a, int b)
{
    printf("%d\n", a + b);
}

template <typename Proc>
void execute(Proc p, int a, int b)
{
    puts("before");

    p(a, b);

    puts("after");
}

int main()
{
    execute(s, 10, 5);

    RangePrinter rp {4, 9};

    // como hemos sobrecargado el operador parentesis, podemos hacer esto.
    // simular el comportamiento de una funcion.
    // rp(10, 5);

    execute(rp, 10, 5);

    RangePrinter rq {6, 15};

    execute(rq, 6, 15);
}