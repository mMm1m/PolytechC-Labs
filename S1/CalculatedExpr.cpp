#include <stdexcept>
#include <limits>
#include "CalculatedExpr.h"

bool is_High_operator(char c);
bool is_Low_operator(char c);
long long golchanskiy::add(long long left, long long right)
{
    if (left > 0 && right > 0)
    {
        long long MAX = std::numeric_limits< long long >::max();
        if (left > MAX - right)
        {
            throw std::overflow_error("Overflow!");
        }
    }
    else if (left < 0 && right < 0)
    {
        long long MIN = std::numeric_limits< long long >::min();
        if (left < MIN - right)
        {
            throw std::overflow_error("Overflow!");
        }
    }
    return left + right;
}
long long golchanskiy::multiplicate(long long left, long long right)
{
    if ((left > 0 && right > 0) || (left < 0 && right < 0))
    {
        long long MAX = std::numeric_limits< long long >::max();
        if (left > MAX / right)
        {
            throw std::overflow_error("Overflow!");
        }
    }
    else if ((left < 0 && right > 0) || (left > 0 && right < 0))
    {
        long long MIN = std::numeric_limits< long long >::min();
        if (left < MIN / right)
        {
            throw std::overflow_error("Overflow!");
        }
    }
    return left * right;
}
long long golchanskiy::divide(long long left, long long right)
{
    if (!right)
    {
        throw std::logic_error("Division by zero!");
    }
    long long MIN = std::numeric_limits< long long >::min();
    if (left == MIN && right == -1)
    {
        throw std::overflow_error("Overflow!");
    }
    return left / right;
}
long long golchanskiy::substraction(long long left,long long right)
{
    return left - right;
}
long long golchanskiy::DivisionWithRemainder(long long left, long long right)
{
    if (!right)
    {
        throw std::logic_error("Division by zero");
    }
    else if (left < 0)
    {
        return left + right * (std::abs(left) / right + 1);
    }
    else
    {
        return left % right;
    }
}
   bool golchanskiy::is_High_operator(char c)
   {
       return c == '*' || c == '/' || c == '%';
   }
   bool golchanskiy::is_Low_operator(char c)
{
    return c == '+' || c == '-';
}

