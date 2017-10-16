#include <cstdio>

void d()
{
    // int* p = nullptr;
    // *p = 2;
    int c = 2/!5;
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