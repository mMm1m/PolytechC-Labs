#ifndef CONST_BI_ITERATOR_H
#define CONST_BI_ITERATOR_H
#include <iterator>

namespace golchanskiy
{
    namespace detail
    {
        template < typename T >
        struct BiNode
        {
            T data_;
            BiNode* next_;
            BiNode* prev_;
        };
    }
    template < typename T >
    class BidirectionalList;
    template < typename T >
    class ConstBiIterator: std::iterator< std::bidirectional_iterator_tag, T >
    {
    public:
        friend class BidirectionalList< T >;
        bool operator==(const ConstBiIterator&) const;
        bool operator!=(const ConstBiIterator&) const;
        ConstBiIterator& operator++();
        ConstBiIterator operator++(int);
        ConstBiIterator& operator--();
        ConstBiIterator operator--(int);
        const T& operator*() const;
        const T* operator->() const;
    private:
        const detail::BiNode< T >* ptr_;
        size_t size;
        explicit ConstBiIterator(const detail::BiNode< T >*);
    };
    template < typename T >
    ConstBiIterator< T >::ConstBiIterator(const detail::BiNode< T >* ptr):
            ptr_(ptr)
    {}
    template < typename T >
    bool ConstBiIterator< T >::operator==(const ConstBiIterator< T >& other) const
    {
        return ptr_ == other.ptr_;
    }
    template < typename T >
    bool ConstBiIterator< T >::operator!=(const ConstBiIterator< T >& other) const
    {
        return !(*this == other);
    }
    template < typename T >
    ConstBiIterator< T >& ConstBiIterator< T >::operator++()
    {
        ptr_ = ptr_->next_;
        return *this;
    }
    template < typename T >
    ConstBiIterator< T > ConstBiIterator< T >::operator++(int)
    {
        ConstBiIterator temp = *this;
        ++(*this);
        return temp;
    }
    template < typename T >
    ConstBiIterator< T >& ConstBiIterator< T >::operator--()
    {
        ptr_ = ptr_->prev_;
        return *this;
    }
    template < typename T >
    ConstBiIterator< T > ConstBiIterator< T >::operator--(int)
    {
        ConstBiIterator temp = *this;
        --(*this);
        return temp;
    }
    template < typename T >
    const T& ConstBiIterator< T >::operator*() const
    {
        return ptr_->data_;
    }
    template < typename T >
    const T* ConstBiIterator< T >::operator->() const
    {
        return std::addressof(ptr_->data_);
    }
}

#endif

