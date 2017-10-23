#include <cstdio>

// Si nuestra clase no tiene metodos virtuales, y no planeamos usarlas para heredar,
// es mejor marcarlas como final.
struct A /* Deberia ser final */
{
    int x;

    // ~A()
    virtual ~A()
    {
        puts("bye A");
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

    // es necesario castear porque la clase padre no tiene este metodo.
    ((B*) a)->p();

    // por que crashea? porque el destructor de A no esta marcado
    // como virtual, si usamos polimorfismo siempre debes marcar
    // el destructor de la clase base como virtual.
    delete a;
}