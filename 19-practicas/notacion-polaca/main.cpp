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
    unordered_map<string, double(*)(double)> ops;
    // operadores binarios
    unordered_map<string, double(*)(double, double)> ops2;

public:
    rpn_evaluator()
    {
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
    }

    void add_op2(const string& s, double (*p)(double, double))
    {
        ops2[s] = p;
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
        return false;
    }

    bool process_op2(vector<double>& stack, const string& token) const
    {
        auto i = ops2.find(token);

        if (i == ops2.end())
            return false;

        if (stack.size() < 2)
            throw "malformed expression";

        double op2 = stack.back();
        stack.pop_back();

        double op1 = stack.back();
        stack.pop_back();

        double r = i->second(op1, op2);

        stack.push_back(r);

        return true;
    }

    void push_token(vector<double>& stack, const string& x) const
    {
        double r = stod(x);
        stack.push_back(r);
    }
};

int main()
{
    rpn_evaluator x;

    auto r = x.eval("14 2 * 2 + 3 /");

    cout << r << "\n";
}

/**
 * Ejercicio: agregar soporte para los operadores :
 * unario: abs, log, sin, cos, tan, ++, --, sqrt, floor, ceiling, !
 * binario: pow(x, y)
 *
 * intentar hacer una funcion template para process_op y quitar process_op1 y process_op2
 */