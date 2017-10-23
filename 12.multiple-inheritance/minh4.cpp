#include <stdio.h>

struct A 
{
    int  n = 8;
    
    void show() const {
        printf("%d\n", n);
    }
};

struct BA: A {};

struct CA: A {};

struct BACA: BA, CA {};

int main()
{
    BACA x;

    // printf("%d\n", x.BA::n);

    x.CA::n = 25;

    x.BA::show();
    x.CA::show();
}