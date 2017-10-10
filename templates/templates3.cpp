#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;

template<typename T>
class ArrayList
{
    T* data;
    size_t n;
    size_t cap;

public:
    // ArrayList(): data((T*) malloc(4*sizeof(T))), n {0}, cap{4}
    // {

    // }
    
    ArrayList(): data(new T[4]), n{0}, cap{4}
    {

    }

    ~ArrayList()
    {
        // free(data);
        delete[] data;
    }

    ArrayList<T>& add(const T& x)
    {
        resize();
        data[n++] = x;

        return *this;
    }

    template<typename Proc>
    void iterate(Proc p) const
    {
        for (auto i = 0U; i < n; i++)
        {
            p(data[i]);
        }
    }

private:
    // void resize()
    // {
    //     if (n == cap)
    //     {
    //         data = (T*) realloc(data, sizeof(T)*(n*2));
    //         cap = n*2;
    //     }
    // }

    void resize()
    {
        if (n == cap)
        {
            T* ndata = new T[cap*2];

            for (auto i = 0U; i < n; i++)
            {
                ndata[i] = data[i];
            }

            cap *= 2;
            delete[] data;
            data = ndata;
        }
    }
};

void show(int p)
{
    printf("%d\n", p);
}

void shows(const string &s)
{
    puts(s.data());
}

int main()
{
    ArrayList<int> x;
    x.add(10).add(15).add(45).add(10).add(18);

    x.iterate(show);

    ArrayList<string> y;

    y.add("hello").add("world").add("of").add("rust").add("coders").add("asdfs").add("ahjgh").add("axcvbcx");

    y.iterate(shows);
}