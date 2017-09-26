// Cuando quisieramos que nuestras clases no seas heredadas?
// Si ponemos final, la clase no podra ser heredada ni habra polimorfismo.

struct X final
{
    int a, b, c;
};

struct Y: X {};