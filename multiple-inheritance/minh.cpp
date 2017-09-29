struct Corredor
{
    void corre()
    {
        puts("corre");
    }
};

struct Volador
{
    void vuela()
    {
        puts("vuela");
    }
};

struct Nadador
{
    void nada()
    {
        puts("nada");
    }
};

struct Mamifero
{

};

struct Ave {};
struct Pez {};

struct Loro: Ave, Volador {};
struct Trucha: Pez, Nadador {};
struct Perro: Mamifero, Corredor {};
struct Ballena: Mamifero, Nadador {};

struct Vehiculo {};

struct Avion: Vehiculo, Volador {};

void doVolar(Volador& p)
{
    p.volar();
}

int main()
{
    Perro p;
    p.corre();

    Loro matias;
    Avion x;

    doVolar(matias);
    doVolar(x);
}
