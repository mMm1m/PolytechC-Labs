#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <iosfwd>
#include "ForwardList.h"
#include "ConstIterator.h"
#include "Iterator.h"

namespace golchanskiy
{
    template < typename Key, typename Value, typename Compare = std::less< Key > >
    class Dictionary
    {
    public:
        Iterator< std::pair< Key, Value > > begin();
        ConstIterator< std::pair< Key, Value > > begin() const;
        Iterator< std::pair< Key, Value > > end();
        ConstIterator< std::pair< Key, Value > > end() const;
        ConstIterator< std::pair< Key, Value > > cbegin() const;
        ConstIterator< std::pair< Key, Value > > cend() const;
        void push(const Key&, const Value&);
        const Value& get(const Key&) const;
        Iterator< std::pair< Key, Value > > find(const Key&);
        ConstIterator< std::pair< Key, Value > > cfind(const Key&) const;
        void pop(const Key&);
        void clear();
        bool isEmpty() const noexcept;
        bool Equals(const Key&, const Key&) noexcept;
    private:
        ForwardList< std::pair< Key, Value > > list_;
        Compare cmp_;
    };
    template < typename Key, typename Value, typename Compare >
    Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::begin()
    {
        return list_.begin();
    }
    template < typename Key, typename Value, typename Compare >
    ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::begin() const
    {
        return list_.begin();
    }
    template < typename Key, typename Value, typename Compare >
    Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::end()
    {
        return list_.end();
    }
    template < typename Key, typename Value, typename Compare >
    ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::end() const
    {
        return list_.end();
    }
    template < typename Key, typename Value, typename Compare >
    ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::cbegin() const
    {
        return list_.cbegin();
    }
    template < typename Key, typename Value, typename Compare >
    ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::cend() const
    {
        return list_.cend();
    }
    template < typename Key, typename Value, typename Compare >
    void Dictionary< Key, Value, Compare >::push(const Key& k, const Value& v)
    {
        if (list_.isEmpty())
        {
            list_.pushBack(std::pair< Key, Value >{k, v});
            return;
        }
        Compare cmp;
        auto it = list_.cbegin();
        if (cmp(k, it->first))
        {
            list_.pushFront(std::pair< Key, Value >{k, v});
            return;
        }
        else if (!cmp(k, it->first) && !cmp(it->first, k))
        {
            list_.popFront();
            list_.pushFront(std::pair< Key, Value >{k, v});
            return;
        }
        auto itNext = ++list_.cbegin();
        while ((itNext != list_.cend()) && cmp(itNext->first, k))
        {
            ++itNext;
            ++it;
        }
        if (itNext == list_.cend())
        {
            list_.pushBack(std::pair< Key, Value >{k, v});
        }
        else if ((itNext != list_.cend()) && !cmp(k, itNext->first) && !cmp(itNext->first, k))
        {
            list_.eraseAfter(it);
            list_.insertAfter(it, std::pair< Key, Value >{k, v});
        }
        else
        {
            list_.insertAfter(it, std::pair< Key, Value >{k, v});
        }
    }
    template < typename Key, typename Value, typename Compare >
    const Value& Dictionary< Key, Value, Compare >::get(const Key& k) const
    {
        auto it = list_.cbegin();
        while (it != cend())
        {
            if (!Compare()(it->first, k) && !Compare()(k, it->first))
            {
                return it->second;
            }
            it++;
        }
        throw std::invalid_argument("Function can't get value");
    }

    template < typename Key, typename Value, typename Compare >
    void Dictionary< Key, Value, Compare >::clear()
    {
        list_.clear();
    }
    template < typename Key, typename Value, typename Compare >
    Iterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::find(const Key& k)
    {
        auto constIt = cfind(k);
        return Iterator< std::pair< Key, Value > >(constIt);
    }
    template < typename Key, typename Value, typename Compare >
    ConstIterator< std::pair< Key, Value > > Dictionary< Key, Value, Compare >::cfind(const Key& k) const
    {
        ConstIterator< std::pair< Key, Value > > it = cbegin();
        Compare cmp;
        while ((it != cend()) && (cmp(it->first, k) || cmp(k, it->first)))
        {
            ++it;
        }
        return it;
    }
    template < typename Key, typename Value, typename Compare >
    void Dictionary< Key, Value, Compare >::pop(const Key& k)
    {
        auto it = list_.cbegin();
        auto nextIt = ++list_.cbegin();
        Compare cmp;
        if (!cmp(it->first, k) && !cmp(k, it->first))
        {
            list_.popFront();
            return;
        }
        while ((it != list_.cend()) && (cmp(nextIt->first, k) || cmp(k, nextIt->first)))
        {
            ++nextIt;
            ++it;
        }
        if (it == list_.cend())
        {
            throw std::logic_error("No such key!\n");
        }
        else
        {
            list_.eraseAfter(it);
        }
    }
    template < typename Key, typename Value, typename Compare >
    bool Dictionary< Key, Value, Compare >::isEmpty() const noexcept
    {
        return list_.isEmpty();
    }
    template < typename Key, typename Value, typename Compare >
    bool golchanskiy::Dictionary<Key, Value, Compare>::Equals(const Key& k1, const Key& k2) noexcept
    {
        return !cmp_(k1, k2) && !cmp_(k2, k1);
    }
}

#endif

