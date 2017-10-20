#include <map>
#include <unordered_map>
#include <iostream>

using namespace std;

struct ci
{
    int n;
    string c;
};

// sobrecargamos el operador <
bool operator<(const ci& a, const ci& b)
{
    // if (a.n < b.n)
    //     return true;

    // if (a.n > b.n)
    //     return false;

    // return a.c < b.c;
    
    return tie(a.n, a.c) < tie(b.n, b.c);
}

struct ci_comp
{
    bool operator()(const ci& a, const ci& b) const
    {
        return tie(a.c, a.n) < tie(b.c, b.n);
    }
}

int main()
{
    // map<ci, unique_ptr<Person>> x;
    // ci_comp puede ser puntero a funcion o functor.
    map<ci, string, ci_comp> x;

    x[ci {6895421, "LP"}] = "Julio Galarza";
    x[ci {6543210, "PT"}] = "Jose Berrios";
    x[ci {7642100, "CB"}] = "Juan Galindo";
    x[ci {123456, "SZ"}] = "Pedro Suarez";
    x[ci {7642100, "BE"}] = "Javier Chavez";

    for (auto& i: x)
    {
        cout << i.first.n << " " << i.first.c << " " << i.second << "\n";
    }
}