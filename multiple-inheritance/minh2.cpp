#include <stdio.h>

class X
{
public:
    int x;
    void p()
    {
        puts("p");
    }
};

class Y
{
public: 
    int x;
    void p()
    {
        puts("q");
    }
};

class Point: public X, public Y
{
public:
    Point(int x, int y) : X {x}, Y {y}
    {

    }

    using X::p;
};

int main()
{
    Point p {10, 20};

    printf("(%d,%d)\n", p.X::x, p.Y::x);

    // p.X::p();
    // p.Y::p();

    p.p();
}

