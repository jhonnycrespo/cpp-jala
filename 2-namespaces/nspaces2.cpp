#include <cstdio>

// namespace X {
//     namespace Y {
//         namespace Z {
//             void f() {
//                 puts("hello");
//             }

//             void g() {
//                 puts("bye");
//             }

//             void m() {
//                 puts(":V");
//             }
//         }
//     }
// }
// 
namespace X = Y::Z
{
    void f() {
        puts("hello");
    }
}

// using namespace X::Y::Z;

int main()
{
    // este operador se llama, operador de ambito
    // X::f();
     
    X::f();

    // g();

    // m();
}