#include <cstring>
#include <cstdlib>
#include <cstdio>

/**
 * Small String Optimization
 */

// Es como usar define.
// MAX_LEN se conoce en tiempo de compilacion
constexpr size_t MAX_LEN = 16;

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

    MyString(const char* s = "")
    {
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

    void show() const
    {
        puts(c_str());
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
            data.str = (char*) malloc(len + 1);
            memcpy(data.str, s, len + 1);
        }
        else
        {
            memcpy(data.sso, s, len + 1);
        }
    }
};

int main()
{
    MyString x = "hello world";

    x += " of programmers";

    x.show();

    MyString a = "juanito";
    MyString b = "juanito";

    if (a == b)
    {
        puts("son iguales");
    }
    else {
        puts("no son iguales");
    }

    MyString c = "hola";
    MyString& q = c;

    if (c == q)
        puts("iguales");

}