#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

// lo declaramos como struct solo porque queremos. Tambien podria ser class.
template<typename T>
struct MallocAllocator
{
    T* init(size_t n) const
    {
        return (T*) malloc(n*sizeof(T));
    }

    void release(T* data, size_t n) const
    {
        free(data);
    }

    void resize(T*& data, size_t n, size_t& capacity) const
    {
        if (n < capacity)
            return;

        data = (T*) realloc(data, (n*2)*sizeof(T));

        capacity *= 2;
    }
};

template<typename T>
struct NewAllocator
{
    T* init(size_t n) const
    {
        return new T[n];
    }

    void release(T* d, size_t s) const
    {
        delete[] d;
    }

    void resize(T*& d, size_t n, size_t& capacity) const
    {
        if (n < capacity)
            return;

        auto nd = new T[n*2];

        for (auto i = 0U; i < n; i++)
        {
            nd[i] = d[i];
        }

        delete[] d;
        d = nd;
        capacity *= 2;
    }
};

// NewAllocator es el valor por defecto.
template<typename T, typename Allocator = NewAllocator<T>>
class ArrayList
{
    T* data;
    // cantidad de elementos que contiene la lista.
    size_t n;
    size_t capacity;
    Allocator alloc;

public:
    // la capacidad inicial del arraylist por defecto es 4
    ArrayList(size_t capacity = 4): data {alloc.init(capacity)}, n {0}, capacity {capacity}
    {

    }

    // puede ser ArrayList<T, Allocator>& en lugar de auto&
    auto& add(const T& x)   
    {
        alloc.resize(data, n, capacity);
        data[n++] = x;
        return *this;
    }

    template<typename Proc>
    void iterate(Proc p)
    {
        for (auto i = 0U; i < n; i++)
        {
            p(data[i]);
        }
    }

    ~ArrayList()
    {
        // le pasamos el numero de elementos. porq??
        alloc.release(data, n);
    }
};

void shows(const string &s)
{
    puts(s.data());
}

void show(int p)
{
    printf("%d\n", p);
}

int main()
{
    ArrayList<int, MallocAllocator<int>> x;
    x.add(10).add(15).add(45).add(10).add(18);
    x.iterate(show);


    // este usa NewAllocator
    ArrayList<string> y;
    y.add("hello").add("world").add("of").add("rust").add("coders").add("asdfs").add("ahjgh").add("axcvbcx");
    y.iterate(shows);
}