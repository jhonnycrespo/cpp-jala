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

    // habilitamos polimorfismo
    virtual void show() const
    {
        puts("********");
        printf("%s\n", nombre);
        printf("%d\n", edad);
    }

    // ???
    virtual ~Persona()
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
    void show() const override
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
    Persona* a = new Persona {"Jigsaw", 70};
    Alumno* b = new Alumno {"Darth Vader", 80, "Devint23"};

    a->show();
    b->show();

    // no imprime curso, porque no es polimorfismo.
    // c no se comporta como Alumno
    Persona* c = new Alumno {"Obi wan", 50, "Devint23"};
    // Para habilitar el polimorfismo tenemos que volver al metodo show "virtual".
    c->show();

    // usando virtual, ganamos polimorfismo pero perdemos un poco de rendimiento.
    // si ponemos virtual se agrega una variable miembro a la clase llamada "vtable"
    
    // tenemos que hacer un casting para hacer esto
    puts(((Alumno*) c)->curso); 
    
    delete a;
    delete b;

    delete c;

    // polimorfismo solo es posible usando punteros.
    // si queremos usarlo con vectores debemos hacer esto:
    // vecto<Persona*>
}
