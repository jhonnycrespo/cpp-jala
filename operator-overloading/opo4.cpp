#include <cstdio>

struct Date
{
    // A las funciones que estan dentro de la clase o estructuras se llaman metodos o functiones miembrosssssss
    int d, m, y;

    void show() const
    {
        // printf("%d - %d - %d\n", d, m ,y);
        // this es puntero, no referencia.
        // No se puede asignar NULL a this.
        printf("%d - %d - %d\n", this->d, this->m , this->y);
    }
};

int main()
{
    Date d {19, 9, 2017};

    d.show();
}

/**
 * En Struct todo sus atributos son publicos por defecto.
 * En una clase todo es private por defecto.
 */