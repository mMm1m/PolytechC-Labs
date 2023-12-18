#ifndef S4_TREENODE_H
#define S4_TREENODE_H

#include <cassert>
#include <algorithm>

namespace golchanskiy {
  template< typename T >
  struct TreeNode {
    using node = TreeNode< T >*;

    T data_;
    int height_;

    node parent_;
    node left_;
    node right_;
  };

  template< typename T >
  int getHeightDifference(TreeNode< T >* node)
  {
    return node->left_->height_ - node->right_->height_;
  }

  template< typename T >
  void fixHeight(TreeNode< T >* node)
  {
    int hleft = node->left_->height_;
    int hright = node->right_->height_;
    node->height_ = std::max(hleft, hright) + 1;
  }
}

#endif
