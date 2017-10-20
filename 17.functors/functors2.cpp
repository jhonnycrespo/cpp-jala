#include <algorithm>

/**
 * [](auto x, auto y) -> int {} es una function anonima o lambda expression
 */

int main()
{
    int arr[] = {4, 8, 9, 5, 1, 20, 2};

    // internamente si [] no tiene parametros, el compilador genera un puntero a function.
    // internamente si [] tiene parametros, el compilador genera un functor.
    qsort(arr, 7, sizeof(int), [](auto x, auto y) -> int {
        auto xx = (int*) x;
        auto yy = (int*) y;

        return *xx - *yy;
    });

    for (auto i: arr)
        printf("%d\n", i);
}