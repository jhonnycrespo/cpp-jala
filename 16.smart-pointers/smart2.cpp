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
    RC<Y> a = new Y{10};
    RC<Y> b = new Y{20};
    RC<Y> c = new Y{30};

    // hay q implementar el constructor copia
    auto d = a;
    auto e = d;
    auto f = a;

    // hay que sobreescribir el operador =
    e = b;
    a = b;
    b = c;
    e = c;

    a->show();
    b->show();
    c->show();
    d->show();
    e->show();
    f->show();
}