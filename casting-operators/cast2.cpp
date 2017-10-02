#include <cstdio>

struct X 
{
    int a;

    virtual ~X() {}
};

struct Y: X
{
    void hi()
    {
        puts("Hi");
    }
};

void say_hi(X& x)
{
    // las excepciones son costosas.
    try
    {
        // si usamos mucho casting, es probable que haya problemas de disenio.
        dynamic_cast<Y&>(x).hi();
    }
    catch(...) // la excepcion que bota es bad_cast
    {
        puts("hola");
    }
}

int main()
{
    X* x = new Y();
    x->a = 10;

    // no compila, por que no hay polimorfismo. Si agregamos un destructor virtual a X, si funciona.
    auto y = dynamic_cast<Y*>(x);

    if (y != nullptr)
        y->hi();

    Y ny;
    say_hi(ny);

    X nx;
    say_hi(nx);

    delete x;
}