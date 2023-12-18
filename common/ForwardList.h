#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <iosfwd>
#include <stdexcept>
#include "Iterator.h"
#include "ConstIterator.h"
#include "List.h"

namespace golchanskiy
{
    template < typename T >
    class ForwardList: public detail::List< T >
    {
    public:
        ForwardList();
        ForwardList(const ForwardList< T >&);
        ForwardList(ForwardList< T >&&) noexcept;
        ~ForwardList();

        Iterator< T > begin();
        ConstIterator< T > begin() const;
        Iterator< T > end();
        ConstIterator< T > end() const;
        ConstIterator< T > cbegin() const;
        ConstIterator< T > cend() const;
        bool isEmpty() const noexcept;
        size_t getSize() const;
        T front() const;
        T back() const;
        Iterator< T > insertAfter(ConstIterator< T >, const T&);
        Iterator< T > eraseAfter(ConstIterator< T >);
        void pushBack(const T&);
        void pushFront(const T&);
        void popFront();
        void popBack();
    };
    template< typename T >
    ForwardList< T >::ForwardList():
            detail::List< T >::List()
    {}

    template< typename T >
    ForwardList< T >::ForwardList(const ForwardList< T >& other):
            detail::List< T >::List(other)
    {}

    template< typename T >
    ForwardList< T >::ForwardList(ForwardList< T >&& other) noexcept:
            detail::List< T >::List(other)
    {}

    template< typename T >
    ForwardList< T >::~ForwardList()
    {
        detail::List<T>::clear();
    }

    template < typename T >
    Iterator< T > ForwardList< T >::begin()
    {
        return Iterator< T >(cbegin());
    }
    template < typename T >
    ConstIterator< T > ForwardList< T >::begin() const
    {
        return ConstIterator< T >(cbegin());
    }
    template < typename T >
    Iterator< T > ForwardList< T >::end()
    {
        return Iterator< T >(cend());
    }
    template < typename T >
    ConstIterator< T > ForwardList< T >::end() const
    {
        return ConstIterator< T >(cend());
    }
    template < typename T >
    ConstIterator< T > ForwardList< T >::cbegin() const
    {
        return ConstIterator< T >(detail::List< T >::head_);
    }
    template < typename T >
    ConstIterator< T > ForwardList< T >::cend() const
    {
        return ConstIterator< T >(nullptr);
    }
    template < typename T >
    bool ForwardList< T >::isEmpty() const noexcept
    {
        return detail::List< T >::isEmpty();
    }
    template < typename T >
    size_t ForwardList< T >::getSize() const
    {
        return detail::List< T >::getSize();
    }
    template < typename T >
    T ForwardList< T >::front() const
    {
        return detail::List< T >::front();
    }
    template < typename T >
    T ForwardList< T >::back() const
    {
        return detail::List< T >::back();
    }
    template < typename T >
    Iterator< T > ForwardList< T >::insertAfter(ConstIterator< T > pos, const T& value)
    {
        auto posPtr_ = const_cast< detail::Node< T >* >(pos.ptr_);
        if (!posPtr_->next_)
        {
            pushBack(value);
            return Iterator< T >(++pos);
        }
        auto temp = posPtr_->next_;
        posPtr_->next_ = new detail::Node< T >{value, temp};
        temp = nullptr;
        ++detail::List< T >::size_;
        return Iterator< T >(++pos);
    }
    template < typename T >
    Iterator< T > ForwardList< T >::eraseAfter(ConstIterator< T > pos)
    {
        auto posPtr_ = const_cast< detail::Node< T >* >(pos.ptr_);
        if (posPtr_->next_ == detail::List< T >::tail_)
        {
            popBack();
            return end();
        }
        auto temp = posPtr_->next_->next_;
        delete posPtr_->next_;
        posPtr_->next_ = temp;
        --detail::List< T >::size_;
        return Iterator< T >(++pos);
    }
    template < typename T >
    void ForwardList< T >::pushBack(const T& data)
    {
        detail::List< T >::pushBack(data);
    }
    template < typename T >
    void ForwardList< T >::pushFront(const T& data)
    {
        detail::List< T >::pushFront(data);
    }
    template < typename T >
    void ForwardList< T >::popFront()
    {
        detail::List< T >::popFront();
    }
    template < typename T >
    void ForwardList< T >::popBack()
    {
        if (!detail::List< T >::size_)
        {
            throw std::logic_error("Pop from empty list");
        }
        if (detail::List< T >::size_ == 1)
        {
            popFront();
            return;
        }
        auto current = detail::List< T >::head_;
        while (current->next_->next_)
        {
            current = current->next_;
        }
        delete current->next_;
        current->next_ = nullptr;
        detail::List< T >::tail_ = current;
        --detail::List< T >::size_;
    }
}

#endif

