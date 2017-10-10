#include <cstdio>
#include <cstdlib>
#include <cstring>

struct P
{
    int* m;

    P(): m(new int[10'000'000])
    {

    }

    ~P()
    {
        puts("Bye P");
    }
};

struct Q
{
    P* p;

    ~Q()
    {
        delete p;
        puts("Bye from Q");
    }
};

// void q()
// {
//     P x;
//     puts("hello");

//     throw 16;

//     puts("Adios");
// }

void q()
{
    Q x {new P()};

    puts("hello");

    throw 16;

    puts("Adios");
}

int main()
{
    P* x = new P();

    try
    {
        q();
    }
    catch(...)
    {
        puts("Error");
    }
}