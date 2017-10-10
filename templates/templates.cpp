#include <cstdio>

struct Int
{
    int n;

    Int operator+(Int b) const
    {
        return Int {n + b.n};
    }
};

// el compilador no genera codigo para esto.
// el cuerpo del template debe estar siempre en el h.
template <typename T>
T sum(T a, T b)
{
    return a + b;
}

template <typename T, typename U>
auto sum(T a, U b) -> decltype(a + b)
{
    return a + b;
}

template <int N, char K>
void repeat()
{
    for ( int i = 0; i < N; i++)
    {
        printf("%c", K);
    }
}

int main()
{
    // cuando el compilador llega aqui, genera una funcion sum<int> a partir del template.
    int p = sum(6, 2);

    // cuando el compilador llega aqui, genera una funcion sum<double>.
    double q = sum(6.4, 9.6);

    // genera una funcion sum<Int>
    // Int x = sum(Int{6}, Int{5});

    // printf("%d %f %d\n", p, q, x.n);

    double m = sum(6, 14.2);
    printf("%f\n", m);

    // el compilador hace el casting a float.
    float f = sum<float, float>(8, 4);
    printf("%f\n", f);

    // repeat();
    
    // los datos que se pasan a <> se evalua en tiempo de compilacion.
    repeat<5, '*'>();
}