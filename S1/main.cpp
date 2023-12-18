#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include "Stack.h"
#include "InfixExpr.h"
#include "PostfixExpr.h"

int main(int argc, char** argv)
{
    golchanskiy::Stack< long long > results;
    std::ifstream fin;
    if (argc == 2)
    {
        fin.open(argv[1]);
        if (!fin.good())
        {
            std::cerr << "Unable to read the file" << std::endl;
            return 1;
        }
    }
    else if (argc > 2)
    {
        std::cerr << "Too many args" << std::endl;
        return 1;
    }
    std::istream& in = argc == 2 ? fin : std::cin;
    try
    {
        while (!in.eof())
        {
            std::string input;
            std::getline(in, input);
            if (!input[0] || input[0] == '\n')
            {
                continue;
            }
            golchanskiy::InfixExpr infixExpr(input);
            golchanskiy::PostfixExpr expr = golchanskiy::PostfixExpr(infixExpr);
            results.push(expr.result());
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 2;
    }
    while (!results.isEmpty())
    {
        std::cout << results.top();
        results.pop();
        if (!results.isEmpty())
        {
            std::cout << ' ';
        }
    }
    std::cout << std::endl;
    return 0;
}

