#ifndef CONST_ITERATOR_H
#define CONST_ITERATOR_H
#include <iosfwd>
#include <stdexcept>
#include <iterator>
#include "List.h"

namespace golchanskiy
{
    template < typename T >
    class ForwardList;
    template < typename T >
    class ConstIterator: public std::iterator< std::forward_iterator_tag, T >
    {
    public:
        friend class ForwardList< T >;
        bool operator ==(const ConstIterator&) const;
        bool operator!=(const ConstIterator&) const;
        ConstIterator& operator++();
        ConstIterator operator++(int);
        const T& operator*() const;
        const T* operator->() const;
    private:
        const detail::Node< T >* ptr_;
        explicit ConstIterator(const detail::Node< T >*);
    };
    template < typename T >
    ConstIterator< T >::ConstIterator(const detail::Node< T >* node):
            ptr_(node)
    {}
    template < typename T >
    bool ConstIterator< T >::operator==(const ConstIterator< T >& other) const
    {
        return ptr_ == other.ptr_;
    }
    template < typename T >
    bool ConstIterator< T >::operator!=(const ConstIterator< T >& other) const
    {
        return !(*this == other);
    }
    template < typename T >
    ConstIterator< T >& ConstIterator< T >::operator++()
    {
        ptr_ = ptr_->next_;
        return *this;
    }
    template < typename T >
    ConstIterator< T > ConstIterator< T >::operator++(int)
    {
        ConstIterator temp = *this;
        ++(*this);
        return temp;
    }
    template < typename T >
    const T& ConstIterator< T >::operator*() const
    {
        return ptr_->data_;
    }
    template < typename T >
    const T* ConstIterator< T >::operator->() const
    {
        return std::addressof(ptr_->data_);
    }
}

#endif

