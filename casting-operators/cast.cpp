int p = (int) 202873629511665LL;
int r = (int) (3.5 / 2.4);
char* p = (char*) malloc(16);
char* s = (char*) "hello" // esto es peligroso

Encoder* e = new FlacEncoder();
// esto compila, pero el resultado es indeterminado
((Mp3Encoder*) e)->getTags();
// Esto tambien funciona.
long long x = (long long) e;

// hay 3 tipos de casting
// No cuestan nada, el tiempo de procesamiento es 0.

// static cast
int x = static_cast<int>(204892LL);
auto p = static_cast<char*>(malloc(15));
static_cast<Mp3Encoder*>(e)->getTags();
char* s = const_cast<char*>("hello");

long long x = reinterpret_cast<long long>(e);



Encoder* e = new Mp3Encoder();
// este casteo se hace en tiempo de ejecucion, tiene un costo.
auto me = dynamic_cast<Mp3Encoder*>(e);

// esto creo q no compila.
auto fe = dynamic_cast<FlacEncoder*>(e);

// nullptr es la version en c++11 de NULL, NULL Y 0 es lo mismo.
if (me != nullptr)
    me->getTags();