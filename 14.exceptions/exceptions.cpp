#include <cstdio>

void d()
{
    throw 16;
    // throw "Virus!!!";
}

void c()
{
    puts("bye");
}

void b()
{
    d();
}

void a()
{
    puts("hola");
    b();
    puts("helloe");
    c();
}

int main()
{
    try
    {
        a();
    }
    //... maneja cualquier excepcion
    catch(const char* e)
    {
        printf("ERROR: %s\n", e);
    }

    catch(...)
    {
        puts("Unknown error");
    }
}