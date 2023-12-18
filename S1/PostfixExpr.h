#ifndef POSTFIXEXPRESSION_H_S1
#define POSTFIXEXPRESSION_H_S1
#include "InfixExpr.h"
#include "Queue.h"

namespace golchanskiy
{
    class PostfixExpr
    {
    public:
        PostfixExpr();
        explicit PostfixExpr(const InfixExpr&);
        ~PostfixExpr() = default;
        bool isEmpty() const;
        char front() const;
        void pop();
        long long result();
    private:
        Queue<char> impl_pstfx_expr;
    };
}

#endif

