#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    vector<string> ss = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "November", "December"};

    // sort es el reemplazo de qsort.
    // sort ordena alfabeticamente todos los elementos entre los rangos.
    // Que pasa si queremos usar otra metodo de ordenamiento??
    sort(ss.begin(), ss.end());

    for (auto& i: ss)
        cout << i << "\n";

    // queremor ordenar por el tamanio de los strings, le pasamos un lambda expression.
    sort(ss.begin(), ss.end(), [](auto& a, auto& b) {
        return a.length() < b.length();
    });

    // Que pasa si queremos enviar alguna bandera para que la function sepa que metodo usar?
    bool ascending = false; 
    
    // no podemos usar ascending directamente en la function anonima, debemos pasarla entre los corchetes.
    // aqui se genera un functor.
    // [=] si ponemos esto se copian todas las variables de afuera (se pasan por valor).
    // [&] tambien podemos pasar por referencia.
    sort(ss.begin(), ss.end(), [ascending](auto& a, auto& b) {
        return ascending ? a.length() < b.length() : b.length() < a.length();
    });

    for (auto& i: ss)
        cout << i << "\n";
}