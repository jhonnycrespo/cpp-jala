#include <cstdio>

namespace X
{
    void f() {
        puts("hello");
    }

    void g() {
        puts("bye");
    }
}

using namespace X;

int main()
{
    // este operador se llama, operador de ambito
    // X::f();
    f();

    ::g();
}