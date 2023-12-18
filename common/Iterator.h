#ifndef ITERATOR_H
#define ITERATOR_H
#include <iosfwd>
#include <stdexcept>
#include <iterator>
#include "List.h"
#include "ConstIterator.h"

namespace golchanskiy
{
    template < typename T >
    class ForwardList;
    template < typename T >
    class Iterator: public std::iterator< std::forward_iterator_tag, T >
    {
    public:
        friend class ForwardList< T >;
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;
        explicit Iterator(const ConstIterator< T >&);
        Iterator& operator++();
        Iterator operator++(int);
        T& operator*();
        T* operator->();
    private:
        ConstIterator< T > impl_iterator_;
    };
    template < typename T >
    Iterator< T >::Iterator(const ConstIterator< T >& other):
            impl_iterator_(other)
    {}
    template < typename T >
    bool Iterator< T >::operator==(const Iterator< T >& other) const
    {
        return impl_iterator_ == other.impl_iterator_;
    }
    template < typename T >
    bool Iterator< T >::operator!=(const Iterator< T >& other) const
    {
        return !(*this == other);
    }
    template < typename T >
    Iterator< T >& Iterator< T >::operator++()
    {
        ++impl_iterator_;
        return *this;
    }
    template < typename T >
    Iterator< T > Iterator< T >::operator++(int)
    {
        return Iterator< T >(impl_iterator_++);
    }
    template < typename T >
    T& Iterator< T >::operator*()
    {
        return const_cast< T& >(*impl_iterator_);
    }
    template < typename T >
    T* Iterator< T >::operator->()
    {
        return const_cast< T* >(std::addressof(*impl_iterator_));
    }
}

#endif

