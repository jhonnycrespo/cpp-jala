#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>

/**
 * Small String Optimization
 */

// Es como usar define.
// MAX_LEN se conoce en tiempo de compilacion
constexpr size_t MAX_LEN = 16;

using namespace std;

// Esto es practicamente lo mismo que una clase. La unica diferencia
// es que los modificares de acceso de las variables y metodos siempre son publicos.
struct MyStringReverseIterator
{
    const char* s;

    bool operator!=(const MyStringReverseIterator& x) const
    {
        return (s != x.s);
    }

    const char& operator*() const
    {
        return *s;
    }

    // ++i
    MyStringReverseIterator& operator++()
    {
        // --s decrementa y devuelve el valor decrementado
        --s;
        return *this;
    }

    // i++
    //int no sirve de nada. solo para que el compilador sepa que este es el i++
    MyStringReverseIterator operator++(int)
    {
        // creamos una copia de this
        auto r = *this;

        --s;

        return r;
    }
};

class MyString
{
    // queremos almacenar el string en el stack y no en el heap segun sea necesario
    union
    {
        // para definir el tamanio de un arreglo usando una constante, si o si tiene que ser
        // constexpr porque la definion del tamanio del arreglo se hace en tiempo de ejecucion y la
        // constante se crea en tiempo de compilacion
        char sso[MAX_LEN];
        char* str;
    } data;

    size_t len;

public:

    // using crea un alias
    using reverse_iterator = MyStringReverseIterator;

    MyString(const char* s = "")
    {
        puts("constructor has been called");
        // strlen no considera el caracter '\0'
        init_str(s, strlen(s));
    }

    // copy constructor - a copy constructor is a member function which initializes an object
    // using another object of the same class.
    MyString(const MyString& src)
    {
        init_str(src.c_str(), src.len);
    }

    MyString& operator=(const MyString& src)
    {
        if (this == &src) return *this;

        this->~MyString();

        init_str(src.c_str(), src.len);

        return *this;
    }

    // const porque no modificamos ni el this, ni el parametro recibido
    MyString operator+(const MyString& src) const
    {
        auto nlen = len + src.len;

        if (nlen >= MAX_LEN)
        {
            auto c = (char*) malloc(nlen + 1);
            memcpy(c, c_str(), len);
            memcpy(c + len, src.c_str(), src.len + 1);

            // aqui no se llama al constructor copia
            // auto r = MyString {c, len};
            // esto es lo mismo que arriba
            // MyString r {c};
            // free(c);
            // return r;
    
            return MyString {c, nlen};
        }

        char aux[MAX_LEN];

        memcpy(aux, data.sso, len);
        memcpy(aux + len, src.data.sso, src.len + 1);

        return MyString {aux};
    }

    MyString& operator+=(const MyString& x)
    {
        auto nlen = len + x.len;

        if (nlen < MAX_LEN)
        {
            memcpy(data.sso + len, x.c_str(), x.len + 1);
            len = nlen;
            return *this;
        }

        // si esta en el stack, hay q crear un espacio en el heap y concatenar x.c_str()
        if (len < MAX_LEN)
        {
            char* nstr = (char*) malloc(nlen + 1);
            memcpy(nstr, data.sso, len);
            memcpy(nstr + len, x.c_str(), x.len + 1);
            data.str = nstr;
            len = nlen;

            return *this;
        }

        // si ya esta en el heap, solo hay que agrandar el espacio en memoria y
        // concatenar x.c_str()
        data.str = (char*) realloc(data.str, nlen + 1);
        memcpy(data.str + len, x.c_str(), x.len + 1);
        len = nlen;

        return *this;
    }

    // const porque no cambiamos el this
    bool operator==(const MyString& x) const
    {
        // si apuntan a la misma direccion
        // this me devuelve dir de memoria
        if (this == &x)
            return true;

        if (len != x.len)
            return false;

        return memcmp(c_str(), x.c_str(), len) == 0;

    }

    const char* c_str() const
    {
        return len >= MAX_LEN ? data.str : data.sso;
    }

    size_t length() const
    {
        return len;
    }

    char operator[](size_t index) const
    {
        return c_str()[index];
    }

    // porque char&?? porque en char& (dir. de memoria) esta el valor que acabamos de guardar
    // la referencias son como punteros
    char& operator[](size_t index)
    {
        // c_str devuelve const char*
        auto c = (char*) c_str();

        return c[index];
    }

    void show() const
    {
        puts(c_str());
    }

    // const porque solo queremos recorrer
    const char* begin() const
    {
        return c_str();
    }

    const char* end() const
    {
        return c_str() + len;
    }

    reverse_iterator rbegin() const
    {
        return reverse_iterator {c_str() + len - 1};
    }

    reverse_iterator rend() const
    {
        return reverse_iterator {c_str() - 1};
    }

    ~MyString()
    {
        if (len >= MAX_LEN)
        {
            free(data.str);
        }
    }

private:
    MyString(char* s, size_t len) : len {len}
    {
        // porque no se puede hacer esto arriba?? porq arriba solo inicializamos
        // data.
        data.str = s;
    }

    void init_str(const char* s, size_t len)
    {
        this->len = len;

        if (len >= MAX_LEN)
        {
            // +1 para el caracter '\0'
            data.str = (char*) malloc(len + 1);
            // + para el caracter '\0'
            memcpy(data.str, s, len + 1);
        }
        else
        {
            // + para el caracter '\0'
            memcpy(data.sso, s, len + 1);
        }
    }
};

int main()
{
    // no llama al metodo operator=
    // llama al constructor
    MyString y = "Wilster-River";
    auto len = y.length();

    // Tenemos que poner U porque len es de tipo size_t y el compilador
    // bota warnings cuando comparamos auto y size_t
    for (auto i = 0U; i < len; i++)
    {
        printf("%c\n", y[i]);
    }

    // y[0] = 'A';
    
    cout << "-------------" << endl;

    // llama al constructor
    const MyString ppp = "hola";
    // printf("%c\n", ppp[2]);
    
    cout << "-------------" << endl;

    // llama al constructor
    MyString ddd = "Todos somos Negan";

    // tambien funciona usando k. Entonces porque usar &k??
    for (auto &k : ddd)
    {
        printf("%zu", sizeof(k));
        printf("%c\n", k);
    }

    //Esto es lo mismo que lo de arriba
    // for (auto it = ddd.begin(); it != ddd.end(); ++it)
    // {
    //     auto& k = *it;
    //     printf("%d\n", k);
    // }

    // llama al constructor
    MyString xyz = "Lucille";

    for (MyString::reverse_iterator i = xyz.rbegin(); i != xyz.rend(); ++i)
    {
        printf("%c\n", *i);
    }
}