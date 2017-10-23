#include <cstdio>

class Encoder
{
public:

    Encoder() {}

    // Si agregamos constructor, ya no hay constructor por defecto y debemos definir uno.
    Encoder(const Encoder& e)
    {
        puts("copying");
    }
    
    // para q este metodo sea sobreescrito, tenemos q ponerle virtual.
    // poniendole = 0 hace que este metodo sea abstracto. Y por tanto la clase se vuelve abstracta.
    // este metodo se llama, metodo virtual puro.
    virtual void encode() = 0;

    // Basta con que un metodo sea virtual, para que el destructor sea virtual.
    virtual ~Encoder() {}
};

class Mp3Encoder: public Encoder
{
public:
    void encode() override
    {
        puts("mp3 coded");
    }
};

class FlacEncoder: public Encoder
{
public:
    void encode() override
    {
        puts("flac coded");
    }
};

// por que no hay polimorfismo??
// al hacer la copia a Encoder estamos perdiendo informacion del objeto original.
// void process(Encoder e)
// {
//     e.encode();
// }
 
// si ponemos const, solo podemos llamar a los metodos constantes.
// void process(const Encoder& e)
// {
//     e.encode();
// }

void process(Encoder& e)
{
    e.encode();
}

int main()
{
    // una clase abstracta no puede instanciarse
    // Encoder e;
    Mp3Encoder m;
    FlacEncoder f;

    // process(e);
    process(m);
    process(f);

    Encoder* s = new Mp3Encoder();
    process(*s);

    delete s;

    // Esto esta mal, porque no se pueden instanciar clases abstractas.
    // Encoder p[6]
    
    // Esto si funciona
    // Encoder* p[6];
}