#include "balanced_bst.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>

// Print the structure of the tree for debugging
void BalancedBST::printTreeStructure() const {
  printTreeStructure(root, 0);
}

void BalancedBST::printTreeStructure(
    const Node *node, const std::function<int(const Node *)> &height) const {
  if (node) {
    std::cout << "Node: " << node->key;
    if (node->parent) {
      std::cout << ", Parent: " << node->parent->key;
    } else {
      std::cout << ", Parent: nullptr";
    }
    if (node->left) {
      std::cout << ", Left Child: " << node->left->key;
    } else {
      std::cout << ", Left Child: nullptr";
    }
    if (node->right) {
      std::cout << ", Right Child: " << node->right->key;
    } else {
      std::cout << ", Right Child: nullptr";
    }
    std::cout << std::endl;
    printTreeStructure(node->left, height);
    printTreeStructure(node->right, height);
  }
}