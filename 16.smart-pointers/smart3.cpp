#include <cstdio>

/**
 * auto_ptr<T>: 
 * unique_ptr<T>: No puede haber dos punteros apuntando al mismo.
 * shared_ptr<T>: Sabe cuantas variables estan apuntando al objeto. Cuando el contador es cero, se destruye.
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
        printf("Bye");
        show();
        // puts("Aye");
    }
};

template <class T>
struct RC
{
    T* p;
    size_t* n;

    RC(T* p): p(p), n(new size_t{1})
    {

    }

    RC(const RC<T>& s): p(s.p), n(s.n)
    {
        (*n)++;
    }

    T* operator->()
    {
        return p;
    }

    RC<T>& operator=(const RC<T>& s)
    {
        if (this == &s)
            return *this;

        this->~RC();

        p = s.p;
        n = s.n;

        (*n)++;

        return *this;
    }

    // nullptr_t ???
    bool operator==(std::nullptr_t) const
    {
        return p == nullptr;
    }

    bool operator==(const RC<T>& x) const
    {
        return p == x.p;
    }

    bool operator==(const T* s) const
    {
        return  p == s;
    }

    T* get() const
    {
        return p;
    }

    T& operator*()
    {
        return *p;
    }

    ~RC()
    {
        (*n)--;

        if (*n == 0)
        {
            delete p;
            delete n;
        }
    }
};

int main()
{
    RC<Y> z = nullptr;

    if (z == nullptr)
        puts("NULL");

    RC<Y> n = nullptr;

    if (z == n)
        puts("Otro NULL");

    // (Y*)0 es un null de tipo Y*
    if (z == (Y*)0)
        puts("Otrisimo NULL");

    RC<Y> a = new Y{10};
    auto& r = *a;
    r.show();
}