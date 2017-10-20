#include <iostream>
#include <map>
#include <unordered_map>

using namespace std;

/**
 * los mapas ordenados por lo general estan implementados como arboles equilibrados.
 */

int main()
{
    // ambos funcionan
    // map<int, string> ps;
    unordered_map<int, string> ps;

    // en c++17 ya no es necesario especificar los tipos de pair<>
    ps.insert(pair<int, string> {1469501, "Jorge Heredia"});

    // make_pair internamente crea un pair.
    ps.insert(make_pair(378302, "Omar Vera"));

    // para insertar elementos esta forma funciona muy bien;
    // para buscar, hay q estar seguros de que el key existe. si no existe,
    // se agregara al mapa con valor null.
    ps[963748] = "Josefa Valencia";

    for (auto& p: ps)
    {
        cout << p.first << ", " << p.second << "\n";
    }

    cout << ps.size() << "\n";

    // ambos funcionan
    // map<int, string>::iterator i = ps.find(378302);
    auto i = ps.find(378302);

    if (i == ps.end())
        cout << "not found\n";
    else
        cout << i->second << "\n";



    if (auto j = ps.find(378302); j == ps.end())
        cout << "not found\n";
    else
        cout << j->second << "\n";
}