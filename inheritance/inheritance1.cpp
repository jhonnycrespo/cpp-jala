#include <cstring>
#include <cstdio>

struct Persona
{
    char nombre[32];
    int edad;

    Persona(const char* s, int e) : edad(e)
    {
        strcpy(nombre, s);
    }

    void show() const
    {
        puts("********");
        printf("%s\n", nombre);
        printf("%d\n", edad);
    }

    ~Persona()
    {
        puts("Bye persona");
    }
};

// en este caso Alumno y Persona deben ser struct. Si uno de ellos es class,
// el compilador da warnings.
// public: todo lo publico de Persona, tambien sera publico en Alumno.
// private: todo lo publico de Persona, sera privado en Alumno
// protected:
struct Alumno : public Persona
{
    char curso[10];

    Alumno(const char* n, int e, const char* c) : Persona(n, e)
    {
        strcpy(curso, c);
    }

    // esto no es polimorfismo, es ocultamiento.
    void show() const
    {
        Persona::show();
        puts(curso);
    }

    ~Alumno()
    {
        puts("bye alumno");
    }
};

int main()
{
    Persona p {"Norman Bates", 30};
    Alumno q {"Freddie Krugger", 50, "Devint23"};

    p.show();
    q.show();
}
