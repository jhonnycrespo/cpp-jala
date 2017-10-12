#include <cstdio>

/**
 * auto_ptr<T>:
 * unique_ptr<T>:
 * shared_ptr<T>: sabe cuantas variables estan apuntando al objeto. Cuando el contador es cero, se destruye.
 * weak_ptr<T>: 
 */

struct Y
{
    int n;

    Y(int num): n {num}
    {
        
    }

    void show() const
    {
        printf("%d\n", n);
    }
    
    ~Y()
    {
        puts("Aye");
    }
};

template <typename T>
struct SP
{
    T* pointer;

    T* operator->()
    {
        return pointer;
    }

    ~SP()
    {
        delete pointer;
    }
};

int main()
{
    // Un smart pointer es una variable de stack que se comporta
    // como puntero.
    SP<Y> y {new Y(12)};
    y->show();

    if (true)
        return 0;

    y->show();
}