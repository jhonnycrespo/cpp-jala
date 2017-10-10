#include <cstdio>

struct X
{
    int n;

    X(int n): n(n)
    {
        printf("hi %d\n", n);

    }

    virtual ~X()
    {

    }
};

struct Y: virtual X
{
    int p;

    Y(int n, int p): X(n), p(p)
    {
        puts("Hi Y");
    }
};

struct Z: virtual X
{
    Z(): X(698)
    {
        puts("Hi Z");

    }
};

struct W: virtual Y, virtual Z
{
    W(int a, int b): Y(a, b), X(125) {}
};

int main()
{
    X* x = new W(8, 0);

    delete x;
}
