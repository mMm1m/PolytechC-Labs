#ifndef BI_ITERATOR_H
#define BI_ITERATOR_H
#include <iterator>
#include "ConstBiIterator.h"

namespace golchanskiy
{
    template < typename T >
    class BidirectionalList;
    template < typename T >
    class BiIterator: public std::iterator< std::bidirectional_iterator_tag, T >
    {
    public:
        friend class BidirectionalList< T >;
        bool operator==(const BiIterator&) const;
        bool operator!=(const BiIterator&) const;
        BiIterator& operator++();
        BiIterator operator++(int);
        BiIterator& operator--();
        BiIterator operator--(int);
        T& operator*();
        T* operator->();
    private:
        ConstBiIterator< T > it_;
        explicit BiIterator(const ConstBiIterator< T >&);
    };
    template < typename T >
    BiIterator< T >::BiIterator(const ConstBiIterator< T >& it):
            it_(it)
    {}
    template < typename T >
    bool BiIterator< T >::operator==(const BiIterator< T >& other) const
    {
        return it_ == other.it_;
    }
    template < typename T >
    bool BiIterator< T >::operator!=(const BiIterator< T >& other) const
    {
        return !(*this == other);
    }
    template < typename T >
    BiIterator< T >& BiIterator< T >::operator++()
    {
        ++it_;
        return *this;
    }
    template < typename T >
    BiIterator< T > BiIterator< T >::operator++(int)
    {
        return BiIterator< T >(it_++);
    }
    template < typename T >
    BiIterator< T >& BiIterator< T >::operator--()
    {
        --it_;
        return *this;
    }
    template < typename T >
    BiIterator< T > BiIterator< T >::operator--(int)
    {
        return BiIterator< T >(it_--);
    }
    template < typename T >
    T& BiIterator< T >::operator*()
    {
        return const_cast< T& >(*it_);
    }
    template < typename T >
    T* BiIterator< T >::operator->()
    {
        return const_cast< T* >(std::addressof(*it_));
    }
}

#endif

