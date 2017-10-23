#include <map>
#include <unordered_map>
#include <iostream>

using namespace std;

struct ci
{
    int num;
    string city;
};

// sobrecargamos el operador <
bool operator<(const ci& a, const ci& b)
{
    // if (a.num < b.num)
    //     return true;

    // if (a.num > b.num)
    //     return false;

    // return a.city < b.city;
    
    return tie(a.num, a.city) < tie(b.num, b.city);
}

struct ci_comp
{
    bool operator()(const ci& a, const ci& b) const
    {
        return tie(a.city, a.num) < tie(b.city, b.num);
    }
};

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
        cout << i.first.num << " " << i.first.city << " " << i.second << "\n";
    }
}