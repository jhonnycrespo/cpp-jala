#include <cstdio>

template <class T>
struct Wrapper
{
    T* x;

    bool is_null() const
    {
        return x == nullptr;
    }

    ~Wrapper()
    {
        delete x;
        puts("bye");
    }
};

void p()
{
    Wrapper<int> x {new int{18}};
    Wrapper<double> y {nullptr};

    printf("%d\n", y.is_null());

    // throw 9;
    // printf("%d\n", *(x.x));
}

int main()
{
    try
    {
        p();
    }
    catch(...)
    {
        puts("Error");
    }
}