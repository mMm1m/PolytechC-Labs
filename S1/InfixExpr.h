#ifndef INFIXEXPRESSION_H_S1
#define INFIXEXPRESSION_H_S1
#include <string>
#include "Queue.h"

namespace golchanskiy
{
    class InfixExpr
    {
    public:
        InfixExpr() = default;
        explicit InfixExpr(const std::string&);
        ~InfixExpr() = default;
        bool isOperation(char);
        void pop();
        char front() const;
        bool isEmpty() const;
    private:
        Queue<char> impl_infx_expr;
    };
}

#endif

