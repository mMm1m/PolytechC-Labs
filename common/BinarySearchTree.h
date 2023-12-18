#ifndef BIN_S_TREE_H
#define BIN_S_TREE_H

#include <utility>
#include <functional>
#include <stdexcept>
#include <cmath>
#include <iterator>
#include "TreeNode.h"
#include "Stack.h"
#include "Queue.h"

namespace golchanskiy {
  template< typename Key, typename Value >
  using node_t = TreeNode< std::pair< Key, Value > >;

  template< typename Key, typename Value, typename Compare = std::less< Key > >
  class BinSTree {
    public:
    class CTreeIt;

    class TreeIt;

    BinSTree():
      root_(nullptr)
    {}

    BinSTree(const BinSTree< Key, Value, Compare >& src):
      root_(nullptr)
    {
      try {
        root_ = copy(src.root_);
      }
      catch (...) {
        clear();
        throw;
      }
    }

    BinSTree(BinSTree< Key, Value, Compare >&& other) noexcept:
      root_(other.root_)
    {
      other.root_ = nullptr;
    }

    ~BinSTree()
    {
      clear();
    }

    BinSTree< Key, Value, Compare >& operator=(const BinSTree< Key, Value, Compare >& src)
    {
      if (this != std::addressof(src)) {
        auto temp = copy(src.root_);
        swap(temp);
        temp = nullptr;
      }
      return *this;
    }

    BinSTree< Key, Value, Compare > operator=(BinSTree< Key, Value, Compare >&& src) noexcept
    {
      if (this != std::addressof(src)) {
        swap(src);
        src.clear();
      }
      return *this;
    }

    TreeIt begin()
    {
      return TreeIt(cbegin());
    }

    CTreeIt begin() const
    {
      return CTreeIt(cfindMin(root_));
    }

    CTreeIt cbegin() const
    {
      return CTreeIt(cfindMin(root_));
    }

    CTreeIt end() const
    {
      return CTreeIt(nullptr);
    }

    CTreeIt cend() const
    {
      return CTreeIt(nullptr);
    }

    TreeIt end()
    {
      return TreeIt(cend());
    }

    template< typename T>
    T traverse_lnr(T value) const
    {
      if (root_ != tmp_node_) {
        golchanskiy::Stack< node_t< Key, Value >* > stack;
        stack.push(root_);
        node_t< Key, Value >* tmp = root_;
        while (!stack.isEmpty()) {
          while (tmp->left_ != tmp_node_) {
            stack.push(tmp->left_);
            tmp = tmp->left_;
          }
          value(stack.top()->data_);
          if (tmp->right_ != tmp_node_) {
            tmp = tmp->right_;
            stack.push(tmp);
          }
        }
      }
      return value;
    }

    template< typename T >
    T traverse_rnl(T value) const
    {
      if (root_ != tmp_node_) {
        Stack< node_t< Key, Value >* > stack;
        stack.push(root_);
        node_t< Key, Value >* tmp = root_;
        while (!stack.isEmpty()) {
          while (tmp->right_ != tmp_node_) {
            stack.push(tmp->right_);
            tmp = tmp->right_;
          }
          value(stack.top()->data_);
          if (stack.top()->left_) {
            tmp = stack.top()->left_;
            stack.pop();
            stack.push(tmp);
          } else
            stack.pop();
        }
      }
      return value;
    }

    template< typename T >
    T traverse_breadth(T value) const
    {
      if (root_ != tmp_node_) {
        golchanskiy::Queue< node_t< Key, Value >* > queue;
        queue.push(root_);
        while (!queue.isEmpty()) {
          node_t< Key, Value >* tmp = queue.front();
          queue.pop();
          value(tmp->data_);
          if (tmp->left_ != tmp_node_)
            queue.push(tmp->left_);
          if (tmp->right_ != tmp_node_)
            queue.push(tmp->right_);
        }
      }
      return value;
    }

    node_t< Key, Value >* insert(const Key& k, const Value& v)
    {
      auto node = new node_t< Key, Value >{std::pair< Key, Value >{k, v}};
      return insertNode(node);
    }

    template< typename... Args >
    node_t< Key, Value >* emplace(const Key& k, Args&& ... args)
    {
      auto node = new node_t< Key, Value >{std::pair< Key, Value >{k, Value(std::forward< Args... >(args...))}};
      return insertNode(node);
    }

    node_t< Key, Value >* erase(const Key& k)
    {
      auto node = find(k);
      return eraseNode(node);
    }

    node_t< Key, Value >* erase(golchanskiy::BinSTree< Key, Value, Compare >::TreeIt it);

    node_t< Key, Value >* rightRotation(node_t< Key, Value >* node)
    {
      if (!node || !node->left_)
        return nullptr;
      node_t< Key, Value >* newNode = node->left_;
      node->left_ = newNode->right_;
      newNode->right_ = node;
      if (node->left_)
        node->left_->parent_ = node;
      newNode->parent_ = node->parent_;
      if (node == root_) {
        root_ = newNode;
        root_->right_->parent_ = newNode;
        return root_;
      } else {
        Compare cmp;
        if (cmp(node->data_.first, node->parent_->data_.first))
          node->parent_->left_ = newNode;
        else
          node->parent_->right_ = newNode;
      }
      node->parent_ = newNode;
      return newNode;
    }

    node_t< Key, Value >* leftRotation(node_t< Key, Value >* node)
    {
      if (!node || !node->right_)
        return nullptr;
      node_t< Key, Value >* newNode = node->right_;
      node->right_ = newNode->left_;
      newNode->left_ = node;
      if (node->right_)
        node->right_->parent_ = node;
      newNode->parent_ = node->parent_;
      if (node == root_) {
        root_ = newNode;
        root_->left_->parent_ = root_;
        return root_;
      } else {
        Compare cmp;
        if (cmp(node->data_.first, node->parent_->data_.first))
          node->parent_->left_ = newNode;
        else
          node->parent_->right_ = newNode;
      }
      node->parent_ = newNode;
      return newNode;
    }

    const node_t< Key, Value >* cfind(const Key& k) const
    {
      if (!root_)
        return nullptr;
      auto current = root_;
      Compare cmp;
      while (current) {
        if (cmp(k, current->data_.first))
          current = current->left_;
        else if (cmp(current->data_.first, k))
          current = current->right_;
        else
          break;
      }
      return current;
    }

    node_t< Key, Value >* find(const Key& k)
    {
      return const_cast< node_t< Key, Value >* >(cfind(k));
    }

    CTreeIt constItFind(const Key& k) const
    {
      return CTreeIt(cfind(k));
    }

    TreeIt itFind(const Key& k)
    {
      return TreeIt(find(k));
    }

    const node_t< Key, Value >* cfindMin(const node_t< Key, Value >* subTree) const
    {
      if (!subTree)
        return nullptr;
      while (subTree->left_) {
        subTree = subTree->left_;
      }
      return subTree;
    }

    const node_t< Key, Value >* cfindMax(const node_t< Key, Value >* subTree) const
    {
      if (!subTree)
        return nullptr;
      while (subTree->right_) {
        subTree = subTree->right_;
      }
      return subTree;
    }

    node_t< Key, Value >* findMin(node_t< Key, Value >* subTree)
    {
      return const_cast< node_t< Key, Value >* >(cfindMin(subTree));
    }

    node_t< Key, Value >* findMax(node_t< Key, Value >* subTree)
    {
      return const_cast< node_t< Key, Value >* >(cfindMax(subTree));
    }

    int getNodeHeight(const node_t< Key, Value >* node) const
    {
      if (!node)
        return -1;
      int leftHeight = getNodeHeight(node->left_);
      int rightHeight = getNodeHeight(node->right_);
      return std::fmax(leftHeight, rightHeight) + 1;
    }

    void clear()
    {
      free(root_);
      root_ = nullptr;
    }

    bool isEmpty() const noexcept
    {
      return !root_;
    }

    void swap(BinSTree< Key, Value, Compare >& other) noexcept
    {
      std::swap(root_, other.root_);
    }

    CTreeIt cupperBound(const Key& k) const
    {
      auto current = clowerBound(k);
      return (current != cend() && (current->first == k)) ? ++current : current;
    }

    TreeIt upperBound(const Key& k)
    {
      return TreeIt(cupperBound(k));
    }

    CTreeIt clowerBound(const Key& k) const
    {
      CTreeIt current(root_);
      Compare cmp;
      while (current != cend()) {
        if (cmp(k, current->first) && (current != cbegin())) {
          auto parent = current;
          --current;
          if (cmp(current->first, k)) {
            current = parent;
            break;
          } else if (!cmp(k, current->first))
            break;
        } else if (cmp(current->first, k)) {
          ++current;
          if ((current != cend()) && !cmp(current->first, k))
            break;
        } else
          break;
      }
      return current;
    }

    TreeIt lowerBound(const Key& k)
    {
      return TreeIt(clowerBound(k));
    }

    private:
    node_t< Key, Value >* root_;
    node_t< Key, Value >* tmp_node_;

    node_t< Key, Value >* insertNode(node_t< Key, Value >* node)
    {
      auto current = root_;
      auto parent = root_;
      if (!current) {
        root_ = node;
        node = nullptr;
        return root_;
      }
      Compare cmp;
      while (current) {
        if (cmp(node->data_.first, current->data_.first))
          current = current->left_;
        else if (cmp(current->data_.first, node->data_.first))
          current = current->right_;
        else {
          if (current->left_) {
            node->left_ = current->left_;
            node->left_->parent_ = node;
          }
          if (current->right_) {
            node->right_ = current->right_;
            node->right_->parent_ = node;
          }
          node->parent_ = current->parent_;
          if (current == root_) {
            root_ = node;
            delete current;
            return node;
          }
          if (cmp(node->data_.first, current->parent_->data_.first))
            current->parent_->left_ = node;
          else
            current->parent_->right_ = node;
          delete current;
          return node;
        }
        if (current)
          parent = current;
      }
      if (cmp(node->data_.first, parent->data_.first))
        parent->left_ = node;
      else
        parent->right_ = node;
      node->parent_ = parent;
      return node;
    }

    node_t< Key, Value >* eraseNode(node_t< Key, Value >* node)
    {
      if (!node)
        return nullptr;
      if (!node->left_ && !node->right_)
        return eraseIfNoChildren(node);
      else if (node->left_ && !node->right_)
        return eraseIfOnlyLeftChild(node);
      else if (!node->left_ && node->right_)
        return eraseIfOnlyRightChild(node);
      return eraseIfTwoChildren(node);
    }

    node_t< Key, Value >* eraseIfNoChildren(node_t< Key, Value >* node)
    {
      Compare cmp;
      if (node == root_) {
        delete root_;
        root_ = nullptr;
        return root_;
      }
      if (cmp(node->data_.first, node->parent_->data_.first))
        node->parent_->left_ = nullptr;
      else
        node->parent_->right_ = nullptr;
      auto temp = node->parent_;
      delete node;
      return temp;
    }

    node_t< Key, Value >* eraseIfOnlyLeftChild(node_t< Key, Value >* node)
    {
      if (node == root_) {
        root_ = root_->left_;
        root_->parent_ = nullptr;
        delete node;
        return root_;
      }
      Compare cmp;
      if (cmp(node->data_.first, node->parent_->data_.first))
        node->parent_->left_ = node->left_;
      else
        node->parent_->right_ = node->left_;
      node->left_->parent_ = node->parent_;
      auto temp = node->parent_;
      delete node;
      return temp;
    }

    node_t< Key, Value >* eraseIfOnlyRightChild(node_t< Key, Value >* node)
    {
      if (node == root_) {
        root_ = root_->right_;
        root_->parent_ = nullptr;
        delete node;
        return root_;
      }
      Compare cmp;
      if (cmp(node->data_.first, node->parent_->data_.first))
        node->parent_->left_ = node->right_;
      else
        node->parent_->right_ = node->right_;
      node->right_->parent_ = node->parent_;
      auto temp = node->parent_;
      delete node;
      return temp;
    }

    node_t< Key, Value >* eraseIfTwoChildren(node_t< Key, Value >* node)
    {
      auto min = findMin(node->right_);
      Compare cmp;
      if (min->right_ && (min->parent_ != node)) {
        min->parent_->left_ = min->right_;
        min->right_->parent_ = min->parent_;
      } else if (min->parent_ != node)
        min->parent_->left_ = nullptr;
      min->right_ = (node->right_->left_) ? node->right_ : node->right_->right_;
      min->left_ = node->left_;
      if (node == root_) {
        min->parent_ = nullptr;
        delete root_;
        root_ = min;
        if (root_->left_)
          root_->left_->parent_ = root_;
        if (root_->right_)
          root_->right_->parent_ = root_;
        return root_;
      }
      min->parent_ = node->parent_;
      node->left_->parent_ = min;
      if (cmp(min->data_.first, min->parent_->data_.first))
        min->parent_->left_ = min;
      else
        min->parent_->right_ = min;
      delete node;
      return min;
    }

    void free(node_t< Key, Value >* subTree)
    {
      if (!subTree)
        return;
      free(subTree->left_);
      free(subTree->right_);
      delete subTree;
    }

    node_t< Key, Value >* copy(const node_t< Key, Value >* subTree)
    {
      if (!subTree)
        return nullptr;
      auto newRoot = new node_t< Key, Value >{subTree->data_};
      newRoot->left_ = copy(subTree->left_);
      if (newRoot->left_)
        newRoot->left_->parent_ = newRoot;
      newRoot->right_ = copy(subTree->right_);
      if (newRoot->right_)
        newRoot->right_->parent_ = newRoot;
      return newRoot;
    }
  };

  template< typename Key, typename Value, typename Comapre >
  const node_t< Key, Value >* getNextNode(const node_t< Key, Value >*);

  template< typename Key, typename Value, typename Comapre >
  const node_t< Key, Value >* getPrevNode(const node_t< Key, Value >*);

  template< typename Key, typename Value, typename Compare >
  class BinSTree< Key, Value, Compare >::CTreeIt: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > > {
    public:
    friend class BinSTree< Key, Value, Compare >;

    CTreeIt(const node_t< Key, Value >* ptr):
      ptr_(ptr)
    {}

    bool operator==(const BinSTree< Key, Value, Compare >::CTreeIt& other) const
    {
      return ptr_ == other.ptr_;
    }

    bool operator!=(const BinSTree< Key, Value, Compare >::CTreeIt& other) const
    {
      return !(*this == other);
    }

    CTreeIt& operator++()
    {
      ptr_ = getNextNode< Key, Value, Compare >(ptr_);
      return *this;
    }

    CTreeIt operator++(int)
    {
      auto temp = *this;
      ++(*this);
      return temp;
    }

    CTreeIt& operator--()
    {
      ptr_ = getPrevNode< Key, Value, Compare >(ptr_);
      return *this;
    }

    CTreeIt operator--(int)
    {
      auto temp = *this;
      --(*this);
      return temp;
    }

    const std::pair< Key, Value >& operator*() const
    {
      return ptr_->data_;
    }

    const std::pair< Key, Value >* operator->() const
    {
      return std::addressof(ptr_->data_);
    }

    private:
    const node_t< Key, Value >* ptr_;
  };

  template< typename Key, typename Value, typename Compare >
  class BinSTree< Key, Value, Compare >::TreeIt: public std::iterator< std::bidirectional_iterator_tag, std::pair< Key, Value > > {
    public:
    friend class BinSTree< Key, Value, Compare >;

    TreeIt(const BinSTree< Key, Value, Compare >::CTreeIt& it):
      it_(it)
    {}

    bool operator==(const BinSTree< Key, Value, Compare >::TreeIt& other) const
    {
      return it_ == other.it_;
    }

    bool operator!=(const BinSTree< Key, Value, Compare >::TreeIt& other) const
    {
      return !(*this == other);
    }

    TreeIt& operator++()
    {
      ++it_;
      return *this;
    }

    TreeIt operator++(int)
    {
      return TreeIt(it_++);
    }

    std::pair< Key, Value >& operator*()
    {
      return const_cast< std::pair< Key, Value >& >(*it_);
    }

    std::pair< Key, Value >* operator->()
    {
      return const_cast< std::pair< Key, Value >* >(std::addressof(*it_));
    }

    private:
    BinSTree< Key, Value, Compare >::CTreeIt it_;
  };

  template< typename Key, typename Value, typename Compare = std::less< Key > >
  const node_t< Key, Value >* getNextNode(const node_t< Key, Value >* node)
  {
    if (!node)
      return nullptr;
    auto current = node;
    Compare cmp;
    if (current->right_) {
      current = current->right_;
      while (current->left_) {
        current = current->left_;
      }
      return current;
    } else if (current->parent_ && cmp(current->data_.first, current->parent_->data_.first))
      return current->parent_;
    while (current->parent_ && cmp(current->parent_->data_.first, current->data_.first)) {
      current = current->parent_;
    }
    return current->parent_;
  }

  template< typename Key, typename Value, typename Compare = std::less< Key > >
  const node_t< Key, Value >* getPrevNode(const node_t< Key, Value >* node)
  {
    if (!node)
      return nullptr;
    auto current = node;
    Compare cmp;
    if (current->left_) {
      current = current->left_;
      while (current->right_) {
        current = current->right_;
      }
      return current;
    } else if (current->parent_ && cmp(current->parent_->data_.first, current->data_.first))
      return current->parent_;
    while (current->parent_ && cmp(current->data_.first, current->parent_->data_.first)) {
      current = current->parent_;
    }
    return current->parent_;
  }
}

#endif

