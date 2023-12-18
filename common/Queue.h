#ifndef QUEUE_H_S1
#define QUEUE_H_S1
#include <stdexcept>
#include "List.h"

namespace golchanskiy
{
    template < typename T >
    class Queue
    {
    public:
        Queue() = default;
        void push(const T&);
        void pop();
        T front() const;
        T back() const;
        bool isEmpty() const;

    private:
        detail::List< T > list_;
    };
}
template < typename T >
T golchanskiy::Queue< T >::front() const
{
    if (isEmpty())
    {
        throw std::logic_error("Queue is empty!");
    }
    return list_.front();
}
template < typename T >
T golchanskiy::Queue< T >::back() const
{
    if (isEmpty())
    {
        throw std::logic_error("Queue is empty!");
    }
    return list_.back();
}
template < typename T >
void golchanskiy::Queue< T >::push(const T& value)
{
    list_.pushBack(value);
}
template < typename T >
void golchanskiy::Queue< T >::pop()
{
    if (isEmpty())
    {
        throw std::logic_error("Queue is empty!");
    }
    list_.popFront();
}
template < typename T >
bool golchanskiy::Queue< T >::isEmpty() const
{
    return list_.isEmpty();
}

#endif

