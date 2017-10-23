#include <cstdio>

// ABC: Abstract Base Class - es una clase q tiene todos los metodos virtuales puros.
class Object
{
    public:
        virtual bool equals(const Object& p) const = 0;
        virtual void show() const = 0;
        virtual ~Object() {}
};

class IComparable: public virtual Object
{
    public:
        virtual int compareTo(const Object& p) const = 0;
};

class Integer: public virtual Object, public virtual IComparable
{
    int n;
    public:
        Integer(int n): n(n)
        {
            
        }

        bool equals(const Object& p) const override
        {
            auto& x = dynamic_cast<const Integer&>(p);
            return n == x.n;
        }

        void show() const override
        {
            printf("%d\n", n);
        }

        int compareTo(const Object& p) const override
        {
            auto& x = dynamic_cast<const Integer&>(p);
            return n - x.n;
        }
};

int main()
{
    Object* x = new Integer(15);
    IComparable* y = new Integer(25);

    printf("%d\n", y->compareTo(*x));

    x->show();
    y->show();

    delete x;
    delete y;

    // Integer x {10};
    // Integer y {10};

    // printf("%d\n", x.compareTo(y));

    // x.show();
    // y.show();
}