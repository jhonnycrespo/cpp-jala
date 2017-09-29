#include <stdio.h>

struct A 
{
    int  n = 8;
};

struct BA: A {};

struct CA: A {};

struct BACA: BA, CA {};

int main()
{
    BACA x;

    printf("%d\n", x.BA::n);

    x.CA::n = 25;

    printf("%d\n", x.CA::n);
    printf("%d\n", x.BA::n);
}