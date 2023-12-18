#ifndef FUNCS_H_S1
#define FUNCS_H_S1
#include <iosfwd>
#include "Queue.h"
#include "InfixExpr.h"
#include "PostfixExpr.h"

namespace golchanskiy
{
    long long add(long long left,long long right);
    long long multiplicate(long long left,long long right);
    long long divide(long long left,long long right);
    long long substraction(long long left,long long right);
    long long DivisionWithRemainder(long long left,long long right);
    bool is_High_operator(char c);
    bool is_Low_operator(char c);
    long long calculatePostfixExpression(PostfixExpr expression);
}

#endif

