#include <cstdio>

class Date
{
    int d, m, y;

public:
    void show() const
    {
        printf("%d - %d - %d\n", this->d, this->m , this->y);
    }

    int get_year() const
    {
        return y;
    }

    Date(int d, int m, int y) : d {d}, m {m}, y {y}
    {

    }
};

class DateRange
{
    Date startDate;
    Date endDate;

public:
    // Los constructores de las clases miembros deben llamarse desde el constructor.
    // La clase Date no tiene constructores sin parametros, si o si 
    // tenemos q inicializar las variables de esta forma:
    DateRange() : startDate {0, 0, 0}, endDate {0, 0, 0}
    {
        // si hacemos asi, bota error
        // startDate = Date {0, 0, 0};
        // endDate = Date {0, 0, 0};
    }

    // DateRange(int d1, int m1, int y1, int d2, int m2, int y2) : startDate(d1, m1, y1), endDate(d2, m2, y2)
    // {}

    DateRange(int d1, int m1, int y1, int d2, int m2, int y2) : DateRange {Date {d1, m1, y1}, Date {d2, m2, y2}}
    {}

    // porq compila? si no proveemos un constructor copia, el compilador lo genera.
    DateRange(const Date& a, const Date& b) : startDate {a}, endDate {b}
    {}

    // const??
    void show() const
    {
        printf("FROM: ");
        startDate.show();
        printf("TO: ");
        endDate.show();
    }

    // El destructor siempre es publico y no recibe parametros
    ~DateRange()
    {
        puts("Bye");
    }
};

int main()
{
    DateRange r;

    DateRange r2 {1, 1, 2016, 31, 12, 2017};

    DateRange r3 {
        Date {1, 2, 2014},
        Date {2, 8, 2015}
    };

    // no tenemos un constructor que reciba un DateRange, pero el compilador lo genera.
    DateRange r4 {r3};

    r.show();
    r2.show();
    r3.show();
    r4.show();

    // RAIL - Resource Acquisition Is Initialization
    // Ya no tenemos que liberar la memoria manualmente (solo para variables de stack)
}