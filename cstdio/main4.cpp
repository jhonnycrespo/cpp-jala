#include <cstdio>

void intercambiar(int x, int y)
{
    int aux = x;
    x = y;
    y = aux;
}

// En c++ ya existe sobrecarga
void intercambiar(const char*& x , const char*& y)
{
    auto z = x;
    x = y;
    y = z;
}

int main()
{
    int a = 8;
    int b = 9;

    intercambiar(a, b);

    printf("%d %d\n", a, b);

    const char* m = "hola";
    auto n = "mundo";
    
    intercambiar(m, n);

    printf("%s %s\n", m, n);
}