#include <cstdio>

// Si nuestra clase no tiene metodos virtuales, y no planeamos usarlas para heredar,
// es mejor marcarlas como final.
struct A /* Deberia ser final */
{
    int x;

    ~A()
    {
        puts("bye");
    }
};

struct B: A
{
    virtual void p()
    {
        puts("hi");
    }

    virtual ~B()
    {
        puts("bye B");
    }
};

int main()
{
    A* a = new B();
    a->x = 100;

    printf("%d\n", a->x);

    ((B*) a)->p();

    // por que crashea?
    delete a;
}