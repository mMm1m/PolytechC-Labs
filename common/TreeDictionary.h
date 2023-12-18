#ifndef S4_TREEDICTIONARY_H
#define S4_TREEDICTIONARY_H

#include <functional>
#include "AVLTree.h"

namespace golchanskiy {
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class TreeDict {
    public:
    using BST = BinSTree< Key, Value, Compare >;
    using iter = typename BST::TreeIt;
    using citer = typename BST::CTreeIt;

    iter begin();

    citer begin() const;

    citer cbegin() const;

    iter end();

    citer end() const;

    citer cend() const;

    citer cfind(const Key&) const;

    iter push(const Key&, const Value&);

    void pop(const Key&);

    iter pop(iter);

    iter pop(iter, iter);

    bool isEmpty() const;

    private:
    AVLTree< Key, Value, Compare > tree_;
  };

  template< typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::iter TreeDict< Key, Value, Compare >::begin()
  {
    return tree_.begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::citer TreeDict< Key, Value, Compare >::begin() const
  {
    return tree_.begin();
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::citer TreeDict< Key, Value, Compare >::cbegin() const
  {
    return tree_.cbegin();
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::iter TreeDict< Key, Value, Compare >::end()
  {
    return tree_.end();
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::citer TreeDict< Key, Value, Compare >::end() const
  {
    return tree_.end();
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::citer TreeDict< Key, Value, Compare >::cend() const
  {
    return tree_.cend();
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::citer TreeDict< Key, Value, Compare >::cfind(const Key& k) const
  {
    return tree_.cfind(k);
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::iter TreeDict< Key, Value, Compare >::push(const Key& k, const Value& v)
  {
    return tree_.insert(k, v);
  }

  template< typename Key, typename Value, typename Compare >
  void TreeDict< Key, Value, Compare >::pop(const Key& k)
  {
    tree_.erase(k);
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::iter TreeDict< Key, Value, Compare >::pop(iter pos)
  {
    return tree_.erase(pos);
  }

  template< typename Key, typename Value, typename Compare >
  typename TreeDict< Key, Value, Compare >::iter TreeDict< Key, Value, Compare >::pop(iter begin, iter end)
  {
    return tree_.erase(begin, end);
  }

  template< typename Key, typename Value, typename Compare >
  bool TreeDict< Key, Value, Compare >::isEmpty() const
  {
    return tree_.isEmpty();
  }
}

#endif
