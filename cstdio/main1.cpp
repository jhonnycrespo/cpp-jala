#include <cstdio>

// desde el estandar 14 el compilador puede deducir el tipo de valor de retorno
auto sum(int a, int b)
{
    return a + b;
}

// estandar 11
auto main() -> int
{
    // auto deduce el tipo de variable dependiendo del valor asignado
    auto a = 2;
    auto b = a + 3;

    puts("Hello World");

    // no compila, si o si tenemos que asignar un valor
    // auto c;
    
    auto x = sum(6, 8);
    printf("%d\n", x); 
}