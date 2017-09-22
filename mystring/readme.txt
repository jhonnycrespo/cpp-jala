const vs  consexpr
==================

https://stackoverflow.com/questions/14116003/difference-between-constexpr-and-const



Both keywords can be used in the declaration of objects as well as functions.

The basic difference when applied to objects is this:


- const declares an object as constant. This implies a guarantee that, once initialized, the value of that object won't change, and the compiler can make use of this fact for optimizations. It also helps prevent the programmer from writing code that modifies objects that were not meant to be modified after initialization.

- constexpr declares an object as fit for use in what the Standard calls constant expressions. But note that constexpr is not the only way to do this.


Constant Expressions
====================

As said above, constexpr declares both objects as well as functions as fit for use in constant expressions. A constant expression is more than merely constant:

- It can be used in places that require compile-time evaluation, for example, template parameters and array-size specifiers:

template<int N>
class fixed_size_list
{ /*...*/ };

fixed_size_list<X> mylist;  // X must be an integer constant expression

int numbers[X];  // X must be an integer constant expression

- But note:

- Declaring something as constexpr does not necessarily guarantee that it will be evaluated at compile time. It can be used for such, but it can be used in other places that are evaluated at run-time, as well.
An object may be fit for use in constant expressions without being declared constexpr. Example:

int main()
{
  const int N = 3;
  int numbers[N] = {1, 2, 3};  // N is constant expression
  return 0;
}

This is possible because N, being constant and initialized at declaration time with a literal, satisfies the criteria for a constant expression, even if it isn't declared constexpr.







- constexpr creates a compile-time constant; const simply means that value cannot be changed





When is copy constructor called?

In C++, a Copy Constructor may be called in following cases:
1. When an object of the class is returned by value.
2. When an object of the class is passed (to a function) by value as an argument.
3. When an object is constructed based on another object of the same class.
4. When compiler generates a temporary object.



When is user defined copy constructor needed?

If we don’t define our own copy constructor, the C++ compiler creates a default copy constructor for each class which does a member wise copy between objects. The compiler created copy constructor works fine in general. We need to define our own copy constructor only if an object has pointers or any run time allocation of resource like file handle, a network connection..etc.



CONST IN FUNCTION DECLARATION
==============================

https://stackoverflow.com/questions/3141087/what-is-meant-with-const-at-end-of-function-declaration
https://stackoverflow.com/questions/751681/meaning-of-const-last-in-a-c-method-declaration


A "const function", denoted with the keyword const after a function declaration, makes it a compiler error for this class function to change a member variable of the class. However, reading of a class variables is ok inside of the function, but writing inside of this function will generate a compiler error.



When you add the const keyword to a method the "this" pointer will essentially become const, and you can therefore not change any member data. (Unless you use mutable, more on that later).