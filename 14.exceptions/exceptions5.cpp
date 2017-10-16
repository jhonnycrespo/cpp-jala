#include <cstdio>
#include <cstdlib>
#include <cstring>

// void h() noexcept
// {
//     throw "hola";
// }

void h() throw (int, char const*)
{
    throw "hola";
}

int main()
{
    try
    {
        h();
    }
    catch (int p)
    {
        printf("%d\n", p);
    }
    catch (...)
    {
        puts("Error");
    }
}