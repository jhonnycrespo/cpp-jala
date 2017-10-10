#include <cstdio>

// Herencia Virtual

struct A
{
    int a;
};

struct B: virtual A
{

};

struct C: virtual A
{

};

struct D: B, C
{

};

int main()
{
    D d;
    d.a = 8;
    d.B::a++;
    d.C::a++;

    printf("%d\n", d.a);
}