#include <cstdio>

int main()
{
    int r = 8;

    int* pr = &r;

    *pr += 4;

    // Se establece la referencia al crearse la variable
    // si creamos una referencia, si o si tenemos que asignarle algo.
    // la relacion se mantiene hasta que las variables salen de ambito.
    // la sintaxis es mas simple.
    // No hay referencias nulas.
    // Permite paso de parametros por referencia
    int& rr = r;

    rr--;

    printf("%d\n", r);
}