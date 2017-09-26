#include <cstdio>

struct A
{
    int n;
    // ponemos constructor para deshabilitar la posibilidad de crear
    // asi A a;
    // el constructor debe tener este signature para que funcion "new A[]", sino se tira.
    A(int n = 0) : n(n) {}

    ~A()
    {
        puts("bye");
    }
};


int main()
{
    // Se llama al constructor
    A a {12};

    // Ya no se puede instanciar de esta forma:
    // A a1;

    // a veces vamos a querer que nuestro objeto se cree en el heap.
    // No se llama al constructor. Y esto es un problema.
    // auto b = (A*) malloc(sizeof(A));

    // para solucionar ese problema en c++ se implemento la instruccion new.
    // En caso de que no haya memoria new devuelve una excepcion. malloc devolvia null, ya no es necesario
    // verificar si A* es null.
    // new se puede sobrecargar
    A* b = new A {5};

    printf("%d\n", b->n);

    // si usamos new, debemos liberar la memoria manualmente
    // delete: primero llama al destructor del objeto, y luego libera la memoria.
    delete b;

    // este operador "new" es diferente al anterior "new" para instanciar un objeto.
    // 10 puede ser conocido en tiempo de ejecucion.
    A* c = new A[10];

    // si usamos new con [] tenemos que llamar a delete[].
    // delete[] llama al constructor de cada elemento del array y
    // luego libera la memoria.
    delete[] c;
}