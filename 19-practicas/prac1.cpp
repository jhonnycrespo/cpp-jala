#include <unordered_map>
#include <iostream>

using namespace std;

struct car
{
    string id;
    string desc;
};

ostream& operator<<(ostream& os, const car& c)
{
    os << "[" << c.id << "] " << c.desc;

    return os;
}

struct person
{
    string ci;
    string name;
};

ostream& operator<<(ostream& os, const person& p)
{
    os << "(" << p.ci << ") " << p.name;

    return os;
}

template <class T>
void add(T& x, const string& ci, const string& name, const string& id, const string& desc)
{
    x[person {ci, name}] = car {id, desc};

}

struct person_hash
{
    size_t operator()(const person& x) const
    {
        hash<string> s;
        return s(x.ci);
    }
};

struct person_eq
{
    bool operator()(const person& a, const person& b) const
    {
        return a.ci == b.ci;
    }
};

template <class K, class V>
ostream& operator<<(ostream& os, const pair<K, V>& p)
{
    os << p.first << " " << p.second;

    return os;
}

int main()
{
    // funciona bien con tipos primitivos.
    // si usamos mapa no ordenado, debemos enviar una funcion que genere un hash.
    // y otra funcion que sepa comparar personas.
    unordered_map<person, car, person_hash, person_eq> x;

    add(x, "1234567PT", "Juan Perez", "123ABC", "Ford T-1");
    add(x, "8636041CB", "Justin Bieber Lopez", "4090XYZ", "Mercedez Classic");

    auto i = x.find(person {"1234567PT", ""});

    if (i == x.end())
        cerr << "Not Found!\n";
    else
    {
        cout << i->first << " " << i->second << "\n";
        cout << *i << "\n";
    }
}