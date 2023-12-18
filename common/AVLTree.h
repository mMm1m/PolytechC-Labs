#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "BinarySearchTree.h"

namespace golchanskiy {
  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class AVLTree {
    public:
    using Iter = typename golchanskiy::BinSTree< Key, Value, Compare >::TreeIt;
    using ConstIter = typename golchanskiy::BinSTree< Key, Value, Compare >::CTreeIt;

    Iter insert(const Key& k, const Value& v)
    {
      auto ptr = tree_.insert(k, v);
      balanceAfterInsertion(ptr);
      return Iter(ConstIter(ptr));
    }

    template< typename... Args >
    Iter emplace(const Key& k, Args&& ... args)
    {
      auto ptr = tree_.emplace(k, std::forward< Args... >(args...));
      balanceAfterInsertion(ptr);
      return Iter(ConstIter(ptr));
    }

    void erase(const Key& k)
    {
      auto current = tree_.erase(k);
      balanceAfterErasure(current);
    }

    Iter erase(Iter beginIt, Iter endIt)
    {
      auto returnable = endIt;
      if (returnable != end())
        ++returnable;
      auto i = beginIt;
      while (i != endIt) {
        i = erase(i);
      }
      return returnable;
    }

    bool isEmpty() const noexcept
    {
      return tree_.isEmpty();
    }

    Iter find(const Key& k)
    {
      return tree_.itFind(k);
    }

    ConstIter cfind(const Key& k) const
    {
      return tree_.constItFind(k);
    }

    Iter begin()
    {
      return tree_.begin();
    }

    ConstIter begin() const
    {
      return tree_.begin();
    }

    ConstIter cbegin() const
    {
      return tree_.cbegin();
    }

    Iter end()
    {
      return tree_.end();
    }

    ConstIter end() const
    {
      return tree_.end();
    }

    ConstIter cend() const
    {
      return tree_.cend();
    }

    ConstIter cupperBound(const Key& k) const
    {
      return tree_.cupperBound(k);
    }

    Iter upperBound(const Key& k)
    {
      return tree_.upperBound(k);
    }

    ConstIter clowerBound(const Key& k) const
    {
      return tree_.clowerBound(k);
    }

    Iter lowerBound(const Key& k)
    {
      return tree_.lowerBound(k);
    }

    template< typename F >
    F traverse_lnr(F f) const
    {
      return tree_.traverse_lnr(f);
    }

    template< typename F >
    F traverse_rnl(F f) const
    {
      return tree_.traverse_rnl(f);
    }

    template< typename F >
    F traverse_breadth(F f) const
    {
      return tree_.traverse_breadth(f);
    }

    private:
    golchanskiy::BinSTree< Key, Value, Compare > tree_;

    golchanskiy::node_t< Key, Value >* rightLeftRotation(golchanskiy::node_t< Key, Value >* node)
    {
      if (!node || !node->parent_ || !node->left_)
        return nullptr;
      auto newNode = tree_.rightRotation(node);
      auto returnable = tree_.leftRotation(newNode->parent_);
      return returnable;
    }

    golchanskiy::node_t< Key, Value >* leftRightRotation(golchanskiy::node_t< Key, Value >* node)
    {
      if (!node || !node->parent_ || !node->right_)
        return nullptr;
      auto newNode = tree_.leftRotation(node);
      auto returnable = tree_.rightRotation(newNode->parent_);
      return returnable;
    }

    void balanceAfterInsertion(golchanskiy::node_t< Key, Value >* current)
    {
      if (current->left_ || current->right_)
        return;
      while (current->parent_) {
        current = current->parent_;
        auto ptr = balance(current);
        if (ptr)
          break;
      }
    }

    golchanskiy::node_t< Key, Value >* balance(golchanskiy::node_t< Key, Value >* node)
    {
      int rightHeight = tree_.getNodeHeight(node->right_);
      int leftHeight = tree_.getNodeHeight(node->left_);
      int balanceFactor = rightHeight - leftHeight;
      if ((balanceFactor == 2) &&
          (tree_.getNodeHeight(node->right_->left_) <= tree_.getNodeHeight(node->right_->right_)))
        return tree_.leftRotation(node);
      else if (balanceFactor == 2)
        return rightLeftRotation(node->right_);
      else if ((balanceFactor == -2) &&
               (tree_.getNodeHeight(node->left_->right_) <= tree_.getNodeHeight(node->left_->left_)))
        return tree_.rightRotation(node);
      else if (balanceFactor == -2)
        return leftRightRotation(node->left_);
      return nullptr;
    }

    void balanceAfterErasure(golchanskiy::node_t< Key, Value >* current)
    {
      if (!current)
        return;
      if (current->right_ && current->left_)
        current = tree_.findMin(current->right_);
      while (current) {
        auto ptr = balance(current);
        if (ptr)
          break;
        current = current->parent_;
      }
    }
  };
}

#endif
