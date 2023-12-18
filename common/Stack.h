#ifndef STACK_H_S1
#define STACK_H_S1
#include <stdexcept>
#include "List.h"

namespace golchanskiy
{
    template < typename T >
    class Stack
    {
    public:
        Stack() = default;
        void push(const T&);
        void pop();
        T top() const;
        bool isEmpty() const;

    private:
        detail::List< T > list_;
    };
}
template < typename T >
void golchanskiy::Stack< T >::push(const T& value)
{
    list_.pushFront(value);
}
template < typename T >
T golchanskiy::Stack< T >::top() const
{
    if (isEmpty())
    {
        throw std::logic_error("Stack is empty!");
    }
    return list_.front();
}
template < typename T >
void golchanskiy::Stack< T >::pop()
{
    if (isEmpty())
    {
        throw std::logic_error("Stack is empty!");
    }
    list_.popFront();
}
template < typename T >
bool golchanskiy::Stack< T >::isEmpty() const
{
    return list_.isEmpty();
}

#endif

