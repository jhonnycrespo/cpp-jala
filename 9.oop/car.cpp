#include <cstring>
#include <cstdlib>
#include <cstdio>

char* ns(const char* s)
{
    auto len = strlen(s);
    char* ss = (char*) malloc(len + 1);
    memcpy(ss, s, len + 1);

    return ss;
}

class CarInfo
{
    // tambien podemos usar strings. Usamos char* solo por motivos de prueba
    char* brand;
    char* model;
    int year;

public:
    // es mejor ponerlos en order, por problemas de rendimiento
    CarInfo(const char* b, const char* m, int y) : brand {ns(b)}, model {ns(m)}, year {y}
    {}

    void show() const
    {
        printf("%s %s (%d)\n", brand, model, year);
    }

    // como hemos creado variables en el heap, debemos liberarlos en el destructor
    ~CarInfo()
    {
        free(brand);
        free(model);

        puts("Bye again");
    }

    // Constructor copia - Recibe como parametro una referencia a si mismo - "this".
    CarInfo(const CarInfo& src) : brand {ns(src.brand)}, model {ns(src.model)}, year {src.year}
    {}

    // Aqui no podemos usar : esto solo esta disponible para el constructor.
    CarInfo& operator=(const CarInfo& c)
    {
        // en caso de a = a
        if (&c == this)
            return *this;

        // primero debemos limpiar los valores de la variable que se esta reasignando.
        this->~CarInfo();

        brand = ns(c.brand);
        model = ns(c.model);
        year = c.year;

        return *this;
    }
};

int main()
{
    CarInfo a {"VW", "Peta", 1970};
    CarInfo b {"Tesla", "4", 2018};

    a.show();
    b.show();

    // este comportamiento es indeterminado. En windows crashea.
    // Para copiar se llama al copyconstructor.
    // Esta es una copia.
    auto c = a;

    c.show();

    // El problema esta al tratar de liberar c, por eso crashea en windows.
    

    // En este caso estamos modificando el valor de un objeto. Esta es una asignacion.
    a = b;
    a.show(); 

    // para que esto funcione hay q devovler CarInfo& desde el metodo operator=
    a = b = c;

    // si hay que implementar destructor, tambien constructor copia y operador igual.
}