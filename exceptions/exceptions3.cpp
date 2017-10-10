#include <cstdio>
#include <cstdlib>
#include <cstring>

struct MyEx
{
    char msg[256];

    MyEx(const MyEx& src)
    {
        strcpy(msg, src.msg);
        puts("copy");
    }

    MyEx(const char* s)
    {
        strcpy(msg, s);
    }
};

void d()
{
    throw MyEx("Wilster 8-0");
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
    catch(const char* e)
    {
        printf("ERROR: %s\n", e);
    }

    catch(const MyEx& ex)
    {
        puts(ex.msg);
    }
    
    //... maneja cualquier excepcion
    catch(...)
    {
        puts("Unknown error");
    }
}