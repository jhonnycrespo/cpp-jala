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
        char sso[MAX_LEN];
        char* str;
    } data;

    size_t len;

public:

    MyString(const char* s = "")
    {
        init_str(s, strlen(s));
    }

    // constructor copy
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
    MyString s;

    MyString s2 = "Hola Mundo";

    MyString s4 = "Jigsaw IT StarWars Annabelle";

    puts(s.c_str());
    puts(s2.c_str());
    puts(s4.c_str());

    MyString s5 = s4;

    s5.show();

    s5 = s2;

    s5.show();

    MyString p = "hello";
    MyString q = "world";

    auto r = p + q;

    r.show();

    r = r + " of software developers";
    r.show();

    MyString u = "hello";   
    // No tenemos un constructor para esto. Por que funciona?
    // El compilador construye MyString con "friends".
    auto v = u + "friends";

    v.show();

    // Por que no funciona?? Porque hello es const char* y lo podemos implementar
    // afuera recibiendo un (const char*, MyString).
    // auto z = "hello" + v;
    
    auto rr = u.operator+("Of C++");
    rr.show();
}