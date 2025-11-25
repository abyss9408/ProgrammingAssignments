#include "balanced_bst.h"
#include <algorithm>
#include <functional>
#include <iostream>

// Node constructor
BalancedBST::Node::Node(double k)
    : key(k), left(nullptr), right(nullptr), parent(nullptr) {}

// Constructor that builds a balanced binary search tree from a vector of keys
// NOTE: THE CODE BELOW IS NOT CORRECT. IT IS JUST A PLACEHOLDER TO ENABLE
// COMPILATION OF THE TESTS. YOU NEED TO IMPLEMENT THE CORRECT FUNCTIONALITY.
BalancedBST::BalancedBST(const std::vector<double> &keys)
    : root(nullptr), size(keys.size()) {
  if (!keys.empty()) {
    // Sort the keys to ensure they are in ascending order
    std::vector<double> sortedKeys = keys;
    std::sort(sortedKeys.begin(), sortedKeys.end());

    // Helper function to recursively build the balanced BST
    std::function<Node*(int, int)> buildTree = [&](int left, int right) -> Node* {
      if (left > right) {
        return nullptr;
      }
      int mid = left + (right - left) / 2; // Find the middle index
      Node *node = new Node(sortedKeys[mid]); // Create the current node
      node->left = buildTree(left, mid - 1); // Recursively build the left subtree
      if (node->left) {
        node->left->parent = node;
      }
      node->right = buildTree(mid + 1, right); // Recursively build the right subtree
      if (node->right) {
        node->right->parent = node;
      }
      return node;
    };

    // Build the tree and assign it to the root
    root = buildTree(0, sortedKeys.size() - 1);
  }
}


// Destructor to clean up the tree
BalancedBST::~BalancedBST() { deleteSubtree(root); }

// Helper function to delete a subtree
void BalancedBST::deleteSubtree(Node *node) {
  if (node) {
    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
  }
}