#include <cstdio>

class Date
{
    // A las funciones que estan dentro de la clase o estructuras se llaman metodos o functiones miembrosssssss
    int d, m, y;

public:
    void show() const
    {
        // printf("%d - %d - %d\n", d, m ,y);
        // this es puntero, no referencia.
        // No se puede asignar NULL a this.
        printf("%d - %d - %d\n", this->d, this->m , this->y);
    }

    int get_year() const
    {
        return y;
    }

    // Esto es mala practica: javalike
    // Date(int d, int m, int y)
    // {
    //     this->d = d;
    //     this->m = m;
    //     this->y = y;
    // }

    // no es necesario usar this.
    Date(int d, int m, int y) : d {d}, m {m}, y {y}
    {

    }
};

int main()
{
    Date d {18, 9, 2017};

    d.show();

    printf("%d\n", d.y);
}

/**
 * En Struct todo sus atributos son publicos por defecto.
 * En una clase todo es private por defecto.
 */