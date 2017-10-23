#include <sstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>

using namespace std;

/**
 * 6, 8, +, 2, *, 3, /
 * 14, 2, *, 2, +, 3, /
 */

/**
 * no necesitamos constructor copia, ni destructor.
 */

class rpn_evaluator
{
    // operadores unarios
    unordered_map<string, double (*)(double)> ops1;
    // operadores binarios
    unordered_map<string, double (*)(double, double)> ops2;

public:
    rpn_evaluator()
    {
        add_op1("abs", [](auto a) {
            return abs(a);
        });

        add_op1("sqrt", [](auto a) {
            return sqrt(a);
        });

        add_op1("floor", [](auto a) {
            return floor(a);
        });

        add_op1("log", [](auto a) {
            return log(a);
        });

        add_op1("sin", [](auto a) {
            return sin(a);
        });

        add_op1("cos", [](auto a) {
            return cos(a);
        });

        add_op1("tan", [](auto a) {
            return tan(a);
        });

        add_op1("ceil", [](auto a) {
            return ceil(a);
        });

        add_op1("++", [](auto a) {
            return a++;
        });

        add_op1("--", [](auto a) {
            return a--;
        });

        add_op2("+", [](auto a, auto b) {
            return a + b;
        });

        add_op2("-", [](auto a, auto b) {
            return a - b;
        });

        add_op2("*", [](auto a, auto b) {
            return a * b;
        });

        add_op2("/", [](auto a, auto b) {
            return a / b;
        });

        add_op2("^", [](auto a, auto b) {
            return pow(a, b);
        });
    }

    void add_op1(const string& op, double (*p)(double))
    {
        ops1[op] = p;
    }

    void add_op2(const string& op, double (*p)(double, double))
    {
        ops2[op] = p;
    }

    double eval(const string& x) const
    {
        auto tokens = parse(x);
        vector<double> stack;

        for (auto& token: tokens)
        {
            bool processed = process_op1(stack, token);

            if (!processed)
                processed = process_op2(stack, token);

            if (!processed)
                push_token(stack, token);
        }

        return stack.back();
    }

private:
    vector<string> parse(const string& x) const
    {
        vector<string> ss;
        // lee hasta encontrar un espacio
        istringstream iss {x};

        while (iss.good())
        {
            string token;
            iss >> token;

            ss.push_back(token);
            cout << token << "\n";
        }
        return ss;
    }

    bool process_op1(vector<double>& stack, const string& token) const
    {
        auto i = ops1.find(token);

        if (i == ops1.end())
            return false;
        
        if (stack.size() < 1)
            throw "malformed expression";

        double op1 = stack.back();

        stack.pop_back();

        double r = i->second(op1);

        stack.push_back(r);

        return true;
    }

    bool process_op2(vector<double>& stack, const string& token) const
    {
        auto i = ops2.find(token);

        if (i == ops2.end())
            return false;

        if (stack.size() < 2)
            throw "malformed expression";

        // back devuelve una referencia al ultimo elemento del vector
        double op2 = stack.back();
        // elimina el ultimo elemento del vector, y reduce el tamanio en uno.
        stack.pop_back();

        double op1 = stack.back();
        stack.pop_back();

        double r = i->second(op1, op2);

        stack.push_back(r);

        return true;
    }

    void push_token(vector<double>& stack, const string& x) const
    {
        // stod converts string to double
        double r = stod(x);
        stack.push_back(r);
    }
};

int main()
{
    rpn_evaluator x;

    auto r = x.eval("3 2 ^ 2 log 14 + 2 * 2 + 3 /");

    cout << r << "\n";
}

/**
 * Ejercicio: agregar soporte para los operadores :
 * unario: abs, log, sin, cos, tan, ++, --, sqrt, floor, ceiling, !
 * binario: pow(x, y)
 *
 * intentar hacer una funcion template para process_op y quitar process_op1 y process_op2
 */