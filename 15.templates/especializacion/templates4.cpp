#include <cstdio>

struct X
{
    int n;
};

template <typename T>
struct Comparator
{
    bool less(const T& a, const T& b)
    {
        puts("Normal");
        return a < b;
    }
};

// Este struct es una especializacion. Solo para tipos X
template <>
struct Comparator<X>
{
    bool less(const X& a, const X& b) const
    {
        puts("Spec X");
        return a.n < b.n;
    }
};

template <typename T>
T xmin(const T& a, const T& b, const T& c)
{
    Comparator<T> cx;

    if (cx.less(a, b) && cx.less(a, c))
        return a;


    if (cx.less(b,a) && cx.less(b, c))
        return b;

    return c;
}

template <typename T>
struct W
{
    T x;

    W(const T& x): x(x)
    {
        puts("created");
    }

    ~W()
    {
        puts("destroyed");
    }

    operator T() const
    {
        puts("casting");
        return x;
    }
};

// este struct tambien es especializacion
template <typename T>
struct W<T*>
{
    T* x;

    W(T* x): x{x}
    {
        puts("Created *");
    }

    ~W()
    {
        puts("Destroyed *");
        delete x;
    }

    operator T() const
    {
        return *x;
    }
};

int main()
{
    // Comparator<int> cint;
    // printf("%d\n", cint.less(6, 9));

    
    // Comparator<X> cx;
    // printf("%d\n", cx.less(X {2}, X {15}));

    // int y = xmin(6, 2, 5);
    // printf("%d\n", y);
    
    auto z = xmin(X {5}, X {4}, X {3});

    printf("%d\n", z.n);

    W<int> x{12};

    printf("%d\n", (int) x);

    W<int*> y{new int{16}};
    printf("%d\n", (int) y);
}

/**
 * Ejercicio:
 * Transformar el arbol bst a template
 */