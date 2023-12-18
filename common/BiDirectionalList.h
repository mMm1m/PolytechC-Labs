#ifndef BIDIRECTIONAL_LIST_H
#define BIDIRECTIONAL_LIST_H
#include <iosfwd>
#include <stdexcept>
#include <initializer_list>
#include "BiIterator.h"
#include "ConstBiIterator.h"
#include "List.h"

namespace golchanskiy
{
    template < typename T >
    class BidirectionalList: public detail::List< T, detail::BiNode< T > >
{
    public:
    using BaseList = detail::List< T, detail::BiNode< T > >;
    BidirectionalList();
    BidirectionalList(const BidirectionalList< T >&);
    BidirectionalList(BidirectionalList< T >&&);
    BidirectionalList(std::initializer_list< T >);
    BidirectionalList& operator=(const BidirectionalList< T >&);
    BidirectionalList& operator=(BidirectionalList< T >&&);
    bool operator==(const BidirectionalList< T >&) const;
    bool operator!=(const BidirectionalList< T >&) const;
    void swap(BidirectionalList< T >&) noexcept;
    BiIterator< T > begin();
    BiIterator< T > end();
    ConstBiIterator< T > begin() const;
    ConstBiIterator< T > end() const;
    ConstBiIterator< T > cbegin() const;
    ConstBiIterator< T > cend() const;
    bool isEmpty() const noexcept;
    size_t getSize() const;
    const T& front() const;
    T& front();
    const T& back() const;
    T& back();
    void clear();
    BiIterator< T > insert(BiIterator< T >, const T&);
    BiIterator< T > erase(BiIterator< T >&);
    BiIterator< T > erase(BiIterator< T >&, BiIterator< T >&);
    void pushBack(const T&);
    void pushFront(const T&);
    void popFront();
    void popBack();
    template < typename... Args >
    void emplaceFront(Args&&...);
    template < typename... Args >
    void emplaceBack(Args&&...);
    template < typename... Args >
    void emplace(ConstBiIterator< T >, Args&&...);
};
template < typename T >
BidirectionalList< T >::BidirectionalList():
        BaseList()
{}
template < typename T >
BidirectionalList< T >::BidirectionalList(const BidirectionalList< T >& other):
        BaseList()
{
    if (!other.isEmpty())
    {
        try
        {
            auto *srcPtr = other.head_;
            do
            {
                pushBack(srcPtr->data_);
                srcPtr = srcPtr->next_;
            } while (srcPtr);
        }
        catch (...)
        {
            clear();
            throw;
        }
    }
}
template < typename T >
BidirectionalList< T >::BidirectionalList(BidirectionalList< T >&& other):
        BaseList(other)
{}
template < typename T >
BidirectionalList< T >::BidirectionalList(std::initializer_list< T > list):
        BaseList()
{
    for (auto && i: list)
    {
        pushBack(i);
    }
}
template < typename T >
BidirectionalList< T >& BidirectionalList< T >::operator=(const BidirectionalList< T >& other)
{
    if (this != std::addressof(other))
    {
        auto temp(other);
        swap(temp);
    }
    return *this;
}
template < typename T >
BidirectionalList< T >& BidirectionalList< T >::operator=(BidirectionalList< T >&& other)
{
    if (this != std::addressof(other))
    {
        swap(other);
        other.clear();
    }
    return *this;
}
template < typename T >
bool BidirectionalList< T >::operator==(const BidirectionalList< T >& other) const
{
    if ((this != std::addressof(other)) && (BaseList::size_ == other.size_))
    {
        auto thisIt = cbegin();
        auto otherIt = other.cbegin();
        while (thisIt != cend())
        {
            if (*thisIt != *otherIt)
                return false;
            ++thisIt;
            ++otherIt;
        }
        return true;
    }
    return this == std::addressof(other);
}
template < typename T >
bool BidirectionalList< T >::operator!=(const BidirectionalList< T >& other) const
{
    return !(*this == other);
}
template < typename T >
void BidirectionalList< T >::swap(BidirectionalList< T >& other) noexcept
{
    BaseList::swap(other);
}
template < typename T >
bool BidirectionalList< T >::isEmpty() const noexcept
{
    return BaseList::isEmpty();
}
template < typename T >
size_t BidirectionalList< T >::getSize() const
{
    return BaseList::getSize();
}
template < typename T >
const T& BidirectionalList< T >::front() const
{
    return BaseList::front();
}
template < typename T >
T& BidirectionalList< T >::front()
{
    return const_cast< T& >(BaseList::front());
}
template < typename T >
const T& BidirectionalList< T >::back() const
{
    return BaseList::back();
}
template < typename T >
T& BidirectionalList< T >::back()
{
    return const_cast< T& >(BaseList::back());
}
template < typename T >
void BidirectionalList< T >::clear()
{
    BaseList::clear();
}
template < typename T >
BiIterator< T > BidirectionalList< T >::insert(BiIterator< T > pos, const T& value)
{
    auto posPtr = const_cast< detail::BiNode< T >* >(pos.it_.ptr_);
    if (pos == begin())
    {
        pushFront(value);
        return pos;
    }
    else if (pos == end())
    {
        pushBack(value);
        return pos;
    }
    detail::BiNode< T >* temp = posPtr->prev_;
    posPtr->prev_ = new detail::BiNode< T >{value, posPtr, temp};
    temp->next_ = posPtr->prev_;
    ++BaseList::size_;
    return ++pos;
}
template < typename T >
BiIterator< T > BidirectionalList< T >::erase(BiIterator< T >& pos)
{
    auto posPtr = const_cast< detail::BiNode< T >* >(pos.it_.ptr_);
    if (pos == end())
        throw std::logic_error("Nothing to erase");
    else if (pos == begin())
    {
        popFront();
        pos = begin();
        return pos;
    }
    else if (posPtr == BaseList::tail_)
    {
        popBack();
        pos = end();
        return pos;
    }
    posPtr->prev_->next_ = posPtr->next_;
    posPtr->next_->prev_ = posPtr->prev_;
    auto temp = posPtr;
    ++pos;
    delete temp;
    --BaseList::size_;
    return pos;
}
template < typename T >
BiIterator< T > BidirectionalList< T >::erase(BiIterator< T >& begin, BiIterator< T >& end)
{
    while (begin != end)
    {
        erase(begin);
    }
    return begin;
}
template < typename T >
void BidirectionalList< T >::pushBack(const T& data)
{
    if (!BaseList::size_)
    {
        BaseList::head_ = new detail::BiNode< T >{data, nullptr, nullptr};
        BaseList::tail_ = BaseList::head_;
    }
    else
    {
        BaseList::tail_->next_ = new detail::BiNode< T >{data, nullptr, BaseList::tail_};
        BaseList::tail_ = BaseList::tail_->next_;
    }
    ++BaseList::size_;
}

}
template < typename T >
void golchanskiy::BidirectionalList< T >::pushFront(const T& data)
{
    detail::BiNode<T>* tail = new detail::BiNode<T>{data};
    if (isEmpty())
        BaseList::tail_ = tail;
    else
    {
        tail->next_ = BaseList::head_;
        BaseList::head_->prev_ = tail;
    }
    BaseList::head_ = tail;
    ++BaseList::size_;
}
template < typename T >
void golchanskiy::BidirectionalList< T >::popFront()
{
    if (isEmpty())
        throw std::logic_error("The list is empty");
    else if (BaseList::size_ == 1)
    {
        delete BaseList::head_;
        BaseList::head_ = nullptr;
        BaseList::tail_ = nullptr;
    }
    else
    {
        detail::BiNode<T>* temp = BaseList::head_;
        BaseList::head_ = BaseList::head_->next_;
        delete temp;
        BaseList::head_->prev_ = nullptr;
    }
    --BaseList::size_;
}
template < typename T >
void golchanskiy::BidirectionalList< T >::popBack()
{
    if (!BaseList::size_)
        throw std::logic_error("Pop from empty list");
    if (BaseList::size_ == 1)
    {
        popFront();
        return;
    }
    detail::BiNode< T >* temp = BaseList::tail_;
    BaseList::tail_ = BaseList::tail_->prev_;
    BaseList::tail_->next_ = nullptr;
    delete temp;
    --BaseList::size_;
}
template < typename T >
golchanskiy::BiIterator< T > golchanskiy::BidirectionalList< T >::begin()
{
    return BiIterator< T >(cbegin());
}
template < typename T >
golchanskiy::BiIterator< T > golchanskiy::BidirectionalList< T >::end()
{
    return BiIterator< T >(cend());
}
template < typename T >
golchanskiy::ConstBiIterator< T > golchanskiy::BidirectionalList< T >::begin() const
{
    return cbegin();
}
template < typename T >
golchanskiy::ConstBiIterator< T > golchanskiy::BidirectionalList< T >::end() const
{
    return cend();
}
template < typename T >
golchanskiy::ConstBiIterator< T > golchanskiy::BidirectionalList< T >::cbegin() const
{
    return ConstBiIterator< T >(BaseList::head_);
}
template < typename T >
golchanskiy::ConstBiIterator< T > golchanskiy::BidirectionalList< T >::cend() const
{
    return ConstBiIterator< T >(nullptr);
}

#endif

